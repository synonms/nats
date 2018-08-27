#ifndef EVENTDESERIALISER_H
#define EVENTDESERIALISER_H

#include <nats-lib_global.h>
#include <messaging/i-event-deserialiser.h>
#include <logging/i-logger.h>

#include <json/ijsonobjectfactory.h>

namespace synonms {
namespace nats {
namespace messaging {

class NATSLIBSHARED_EXPORT EventDeserialiser : public IEventDeserialiser
{
public:
	EventDeserialiser(std::shared_ptr<logging::ILogger> logger, std::shared_ptr<json::IJsonObjectFactory> jsonObjectFactory);
	~EventDeserialiser() override;

	std::unique_ptr<events::Event> deserialise(const std::string& data) override;

private:
	class Implementation;
	std::unique_ptr<Implementation> implementation;
};

}}}

#endif
