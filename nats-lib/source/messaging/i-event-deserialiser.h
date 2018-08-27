#ifndef IEVENTDESERIALISER_H
#define IEVENTDESERIALISER_H

#include <messaging/events/event.h>
#include <nats-lib_global.h>

#include <memory>
#include <string>

namespace synonms {
namespace nats {
namespace messaging {

class NATSLIBSHARED_EXPORT IEventDeserialiser
{
public:
	virtual ~IEventDeserialiser() = default;
	virtual std::unique_ptr<events::Event> deserialise(const std::string& data) = 0;
};

}}}

#endif
