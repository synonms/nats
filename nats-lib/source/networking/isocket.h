#ifndef ISOCKET_H
#define ISOCKET_H

#include <nats-lib_global.h>

#include <cstdint>
#include <memory>
#include <string>

namespace synonms {
namespace nats {
namespace networking {

class NATSLIBSHARED_EXPORT ISocket
{

public:
	virtual ~ISocket() = default;

	// TODO - do this event/delegate stuff properly
	std::vector<std::function<void()>> ConnectedEventHandlers;
	std::vector<std::function<void()>> DisconnectedEventHandlers;
	std::vector<std::function<void(std::string)>> SocketErrorEventHandlers;
	std::vector<std::function<void(std::vector<std::string>)>> SslErrorEventHandlers;
	std::vector<std::function<void(std::string)>> ReadyReadEventHandlers;

	virtual void connect(const std::string& host, uint16_t port) = 0;
	virtual void disconnect() = 0;
	virtual void send(const std::string& message) = 0;
};

}}}

#endif
