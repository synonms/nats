#include "info-event.h"

using namespace synonms::nats::messaging::events;

InfoEvent::InfoEvent()
	: Event(EventType::Info)
{
}
