#ifndef QTSOCKET_H
#define QTSOCKET_H

#include <networking/isocket.h>
#include <nats-lib_global.h>

#include <functional>

#include <QObject>
#include <QSslSocket>

namespace synonms {
namespace nats {
namespace networking {

class NATSLIBSHARED_EXPORT QtSocket : public QObject, public ISocket
{
	Q_OBJECT

public:
	explicit QtSocket(QObject* parent = nullptr);
	~QtSocket() override;

	std::vector<std::function<void()>> _connectedEventHandlers;
	std::vector<std::function<void()>> _disconnectedEventHandlers;
	std::vector<std::function<void(std::string&&)>> _socketErrorEventHandlers;
	std::vector<std::function<void(std::vector<std::string>&&)>> _sslErrorEventHandlers;
	std::vector<std::function<void(std::vector<uint8_t>&&)>> _readyReadEventHandlers;

	void Connect(const std::string& host, uint16_t port) override;
	void Disconnect() override;

private slots:

	void ConnectedDelegate();
	void DisconnectedDelegate();
	void SocketErrorDelegate(QAbstractSocket::SocketError socketError);
	void SslErrorDelegate(const QList<QSslError>& sslErrors);
	void ReadyReadDelegate();

private:
	QSslSocket _socket;

};

}}}

#endif
