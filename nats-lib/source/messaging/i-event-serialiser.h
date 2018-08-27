#ifndef IEVENTSERIALISER_H
#define IEVENTSERIALISER_H

#include <messaging/events/event.h>
#include <nats-lib_global.h>

#include <string>

namespace synonms {
namespace nats {
namespace messaging {

class NATSLIBSHARED_EXPORT IEventSerialiser
{
public:
	virtual ~IEventSerialiser() = default;
	virtual std::string serialise(events::Event* event) = 0;
};

}}}

#endif
