#include "connect-event.h"

using namespace synonms::nats::messaging::events;

ConnectEvent::ConnectEvent()
	: Event(EventType::Connect)
{
}
