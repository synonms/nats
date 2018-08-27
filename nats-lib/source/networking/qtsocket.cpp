#include "qtsocket.h"

#include <QAbstractSocket>
#include <QSslError>

using namespace synonms::nats::logging;
using namespace synonms::nats::networking;

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

class QtSocket::Implementation
{
public:
	Implementation(std::shared_ptr<ILogger> logger)
		: logger(logger)
	{
	}

	std::shared_ptr<ILogger> logger;
	QSslSocket socket;
};

QtSocket::QtSocket(std::shared_ptr<ILogger> logger, QObject* parent)
	: QObject(parent)
{
	implementation.reset(new Implementation(logger));

	QObject::connect(&implementation->socket, &QSslSocket::connected, this, &QtSocket::connectedDelegate);
	QObject::connect(&implementation->socket, &QSslSocket::disconnected, this, &QtSocket::disconnectedDelegate);
	QObject::connect(&implementation->socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &QtSocket::socketErrorDelegate);
	QObject::connect(&implementation->socket, static_cast<void(QSslSocket::*)(const QList<QSslError> &)>(&QSslSocket::sslErrors), this, &QtSocket::sslErrorDelegate);
	QObject::connect(&implementation->socket, &QSslSocket::readyRead, this, &QtSocket::readyReadDelegate);
}

QtSocket::~QtSocket()
{
}

void QtSocket::connect(const std::string& host, uint16_t port)
{
	if (implementation->socket.isOpen()) return;

	implementation->logger->debug("Connecting...", LOG_DEFAULTS);

	implementation->socket.connectToHost(QString(host.c_str()), port);
}

void QtSocket::disconnect()
{
	if (!implementation->socket.isOpen()) return;

	implementation->logger->debug("Disconnecting...", LOG_DEFAULTS);

	implementation->socket.disconnectFromHost();
}

void QtSocket::send(const std::string& message)
{
	implementation->logger->debug("Sending " + message, LOG_DEFAULTS);;

	implementation->socket.write(message.c_str());
}

void QtSocket::connectedDelegate()
{
	implementation->logger->debug("Connected", LOG_DEFAULTS);

	for(const auto& func : ConnectedEventHandlers) func();
}

void QtSocket::disconnectedDelegate()
{
	implementation->logger->debug("Disconnected", LOG_DEFAULTS);

	for(const auto& func : DisconnectedEventHandlers) func();
}

void QtSocket::socketErrorDelegate(QAbstractSocket::SocketError socketError)
{
	implementation->logger->debug("SocketError", LOG_DEFAULTS);

	auto errorMessage = std::string("Unknown");

	if (socketErrorMapper.find(socketError) != std::end(socketErrorMapper)) errorMessage = socketErrorMapper.at(socketError);

	for(const auto& func : SocketErrorEventHandlers) func(errorMessage);
}

void QtSocket::sslErrorDelegate(const QList<QSslError>& sslErrors)
{
	implementation->logger->debug("SslError", LOG_DEFAULTS);

	std::vector<std::string> errorMessages;

	for(const auto& sslError : sslErrors)
	{
		auto errorMessage = std::string("Unknown");

		if (sslErrorMapper.find(sslError.error()) != std::end(sslErrorMapper)) errorMessage = sslErrorMapper.at(sslError.error());

		errorMessages.push_back(errorMessage);
	}

	for(const auto& func : SslErrorEventHandlers) func(errorMessages);
}

void QtSocket::readyReadDelegate()
{
	implementation->logger->debug("ReadyRead", LOG_DEFAULTS);

	auto data = implementation->socket.readAll();

	implementation->logger->debug("Read " + std::to_string(data.size()) + " bytes", LOG_DEFAULTS);

	for(const auto& func : ReadyReadEventHandlers) func(data.toStdString());
}
