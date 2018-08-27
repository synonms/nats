#ifndef QTSOCKET_H
#define QTSOCKET_H

#include <nats-lib_global.h>
#include <networking/isocket.h>
#include <logging/i-logger.h>

#include <functional>
#include <memory>

#include <QObject>
#include <QSslSocket>

namespace synonms {
namespace nats {
namespace networking {

class NATSLIBSHARED_EXPORT QtSocket : public QObject, public ISocket
{
	Q_OBJECT

public:
	explicit QtSocket(std::shared_ptr<logging::ILogger> logger, QObject* parent = nullptr);
	~QtSocket() override;

	void connect(const std::string& host, uint16_t port) override;
	void disconnect() override;
	void send(const std::string& message) override;

private slots:
	void connectedDelegate();
	void disconnectedDelegate();
	void socketErrorDelegate(QAbstractSocket::SocketError socketError);
	void sslErrorDelegate(const QList<QSslError>& sslErrors);
	void readyReadDelegate();

private:
	class Implementation;
	std::unique_ptr<Implementation> implementation;
};

}}}

#endif
