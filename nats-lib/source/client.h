#ifndef CLIENT_H
#define CLIENT_H

#include <nats-lib_global.h>
#include <logging/i-logger.h>
#include <networking/isocket.h>
#include <messaging/i-event-broker.h>
#include <messaging/i-event-deserialiser.h>

#include <memory>

namespace synonms {
namespace nats {

class NATSLIBSHARED_EXPORT Client
{
public:
	Client(std::shared_ptr<logging::ILogger> logger, std::shared_ptr<networking::ISocket> socket, std::shared_ptr<messaging::IEventDeserialiser> eventDeserialiser, std::shared_ptr<messaging::IEventBroker> eventBroker);
	~Client();

	void publish(const std::string& subject, const std::vector<uint8_t>& data);
	void subscribe(const std::string& subject, const std::function<void()> newMessageDelegate);

private:
	class Implementation;
	std::unique_ptr<Implementation> implementation;
};

}}

#endif
