#include "qtsocket.h"

#include <QAbstractSocket>
#include <QSslError>

namespace synonms {
namespace nats {
namespace networking {

static const std::map<QAbstractSocket::SocketError, std::string> socketErrorMapper = {
	{QAbstractSocket::ConnectionRefusedError, "ConnectionRefusedError"}
	, {QAbstractSocket::RemoteHostClosedError, "RemoteHostClosedError"}
	, {QAbstractSocket::HostNotFoundError, "HostNotFoundError"}
	, {QAbstractSocket::SocketAccessError, "SocketAccessError"}
	, {QAbstractSocket::SocketResourceError, "SocketResourceError"}
	, {QAbstractSocket::SocketTimeoutError, "SocketTimeoutError"}
	, {QAbstractSocket::DatagramTooLargeError, "DatagramTooLargeError"}
	, {QAbstractSocket::NetworkError, "NetworkError"}
	, {QAbstractSocket::AddressInUseError, "AddressInUseError"}
	, {QAbstractSocket::SocketAddressNotAvailableError, "SocketAddressNotAvailableError"}
	, {QAbstractSocket::UnsupportedSocketOperationError, "UnsupportedSocketOperationError"}
	, {QAbstractSocket::ProxyAuthenticationRequiredError, "ProxyAuthenticationRequiredError"}
	, {QAbstractSocket::SslHandshakeFailedError, "SslHandshakeFailedError"}
	, {QAbstractSocket::UnfinishedSocketOperationError, "UnfinishedSocketOperationError"}
	, {QAbstractSocket::ProxyConnectionRefusedError, "ProxyConnectionRefusedError"}
	, {QAbstractSocket::ProxyConnectionClosedError, "ProxyConnectionClosedError"}
	, {QAbstractSocket::ProxyConnectionTimeoutError, "ProxyConnectionTimeoutError"}
	, {QAbstractSocket::ProxyNotFoundError, "ProxyNotFoundError"}
	, {QAbstractSocket::ProxyProtocolError, "ProxyProtocolError"}
	, {QAbstractSocket::OperationError, "OperationError"}
	, {QAbstractSocket::SslInternalError, "SslInternalError"}
	, {QAbstractSocket::SslInvalidUserDataError, "SslInvalidUserDataError"}
	, {QAbstractSocket::TemporaryError, "TemporaryError"}
	, {QAbstractSocket::UnknownSocketError, "UnknownSocketError"}
};

static const std::map<QSslError::SslError, std::string> sslErrorMapper = {
	{QSslError::NoError, "NoError"}
	, {QSslError::UnableToGetIssuerCertificate, "UnableToGetIssuerCertificate"}
	, {QSslError::UnableToDecryptCertificateSignature, "UnableToDecryptCertificateSignature"}
	, {QSslError::UnableToDecodeIssuerPublicKey, "UnableToDecodeIssuerPublicKey"}
	, {QSslError::CertificateSignatureFailed, "CertificateSignatureFailed"}
	, {QSslError::CertificateNotYetValid, "CertificateNotYetValid"}
	, {QSslError::CertificateExpired, "CertificateExpired"}
	, {QSslError::InvalidNotBeforeField, "InvalidNotBeforeField"}
	, {QSslError::InvalidNotAfterField, "InvalidNotAfterField"}
	, {QSslError::SelfSignedCertificate, "SelfSignedCertificate"}
	, {QSslError::SelfSignedCertificateInChain, "SelfSignedCertificateInChain"}
	, {QSslError::UnableToGetLocalIssuerCertificate, "UnableToGetLocalIssuerCertificate"}
	, {QSslError::UnableToVerifyFirstCertificate, "UnableToVerifyFirstCertificate"}
	, {QSslError::CertificateRevoked, "CertificateRevoked"}
	, {QSslError::InvalidCaCertificate, "InvalidCaCertificate"}
	, {QSslError::PathLengthExceeded, "PathLengthExceeded"}
	, {QSslError::InvalidPurpose, "InvalidPurpose"}
	, {QSslError::CertificateUntrusted, "CertificateUntrusted"}
	, {QSslError::CertificateRejected, "CertificateRejected"}
	, {QSslError::SubjectIssuerMismatch, "SubjectIssuerMismatch"}
	, {QSslError::AuthorityIssuerSerialNumberMismatch, "AuthorityIssuerSerialNumberMismatch"}
	, {QSslError::NoPeerCertificate, "NoPeerCertificate"}
	, {QSslError::HostNameMismatch, "HostNameMismatch"}
	, {QSslError::UnspecifiedError, "UnspecifiedError"}
	, {QSslError::NoSslSupport, "NoSslSupport"}
	, {QSslError::CertificateBlacklisted, "CertificateBlacklisted"}
};

QtSocket::QtSocket(QObject* parent)
	: QObject(parent)
{
	QObject::connect(&_socket, &QSslSocket::connected, this, &QtSocket::ConnectedDelegate);
	QObject::connect(&_socket, &QSslSocket::disconnected, this, &QtSocket::DisconnectedDelegate);
	QObject::connect(&_socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &QtSocket::SocketErrorDelegate);
	QObject::connect(&_socket, static_cast<void(QSslSocket::*)(const QList<QSslError> &)>(&QSslSocket::sslErrors), this, &QtSocket::SslErrorDelegate);
	QObject::connect(&_socket, &QSslSocket::readyRead, this, &QtSocket::ReadyReadDelegate);
}

QtSocket::~QtSocket()
{
}

void QtSocket::Connect(const std::string& host, uint16_t port)
{
	if (_socket.isOpen()) return;

	qDebug() << "Connecting...";

	_socket.connectToHost(QString(host.c_str()), port);
}

void QtSocket::Disconnect()
{
	if (!_socket.isOpen()) return;

	qDebug() << "Disconnecting...";

	_socket.disconnectFromHost();
}

void QtSocket::ConnectedDelegate()
{
	qDebug() << "ConnectedDelegate()";

	for(const auto& func : _connectedEventHandlers) func();
}

void QtSocket::DisconnectedDelegate()
{
	qDebug() << "DisconnectedDelegate()";

	for(const auto& func : _disconnectedEventHandlers) func();
}

void QtSocket::SocketErrorDelegate(QAbstractSocket::SocketError socketError)
{
	auto errorMessage = std::string("Unknown");

	if (socketErrorMapper.find(socketError) != std::end(socketErrorMapper)) errorMessage = socketErrorMapper.at(socketError);

	for(const auto& func : _socketErrorEventHandlers) func(std::move(errorMessage));
}

void QtSocket::SslErrorDelegate(const QList<QSslError>& sslErrors)
{
	std::vector<std::string> errorMessages;

	for(const auto& sslError : sslErrors)
	{
		auto errorMessage = std::string("Unknown");

		if (sslErrorMapper.find(sslError.error()) != std::end(sslErrorMapper)) errorMessage = sslErrorMapper.at(sslError.error());

		errorMessages.push_back(errorMessage);
	}

	for(const auto& func : _sslErrorEventHandlers) func(std::move(errorMessages));
}

void QtSocket::ReadyReadDelegate()
{
	auto data = _socket.readAll();

	std::vector<uint8_t> message(data.begin(), data.end());

	if(message.empty()) return;

	for(const auto& func : _readyReadEventHandlers) func(std::move(message));
}
}}}
