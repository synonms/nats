#ifndef EVENTSERIALISER_H
#define EVENTSERIALISER_H

#include <nats-lib_global.h>
#include <messaging/i-event-serialiser.h>
#include <json/ijsonobjectfactory.h>
#include <logging/i-logger.h>

#include <memory>

namespace synonms {
namespace nats {
namespace messaging {

class NATSLIBSHARED_EXPORT EventSerialiser : public IEventSerialiser
{
public:
	EventSerialiser(std::shared_ptr<logging::ILogger> logger, std::shared_ptr<json::IJsonObjectFactory> jsonObjectFactory);
	~EventSerialiser() override;

	std::string serialise(events::Event* event) override;

private:
	class Implementation;
	std::unique_ptr<Implementation> implementation;
};

}}}

#endif
