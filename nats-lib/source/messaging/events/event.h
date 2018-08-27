#ifndef EVENT_H
#define EVENT_H

#include <messaging/events/event-type.h>
#include <nats-lib_global.h>

namespace synonms {
namespace nats {
namespace messaging {
namespace events {

class NATSLIBSHARED_EXPORT Event
{
public:
	Event(EventType type) : _type(type) {}
	virtual ~Event() = default;
	EventType type() { return _type; }

private:
	EventType _type {EventType::Unknown};
};

}}}}

#endif
