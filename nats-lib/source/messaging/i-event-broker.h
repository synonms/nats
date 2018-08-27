#ifndef IEVENTBROKER_H
#define IEVENTBROKER_H

#include <memory>

#include <messaging/handlers/i-event-handler.h>
#include <nats-lib_global.h>

namespace synonms {
namespace nats {
namespace messaging {

class NATSLIBSHARED_EXPORT IEventBroker
{
public:
	virtual ~IEventBroker() = default;
	virtual void addHandler(std::unique_ptr<handlers::IEventHandler> handler) = 0;
	virtual void delegate(events::Event* event) = 0;
};

}}}

#endif
