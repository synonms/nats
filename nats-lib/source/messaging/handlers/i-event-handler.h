#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H

#include <messaging/events/event.h>
#include <messaging/events/event-type.h>
#include <nats-lib_global.h>

namespace synonms {
namespace nats {
namespace messaging {
namespace handlers {

class NATSLIBSHARED_EXPORT IEventHandler
{
public:
	virtual ~IEventHandler() = default;
	virtual events::EventType type() const = 0;
	virtual void process(events::Event* event) = 0;
};

}}}}

#endif
