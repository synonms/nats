#ifndef EVENTBROKER_H
#define EVENTBROKER_H

#include <messaging/i-event-broker.h>
#include <nats-lib_global.h>
#include <logging/i-logger.h>

#include <vector>

namespace synonms {
namespace nats {
namespace messaging {

class NATSLIBSHARED_EXPORT EventBroker : public IEventBroker
{
public:
	EventBroker(std::shared_ptr<logging::ILogger> logger);
	~EventBroker() override;
	void addHandler(std::unique_ptr<handlers::IEventHandler> handler) override;
	void delegate(events::Event* event) override;

private:
	class Implementation;
	std::unique_ptr<Implementation> implementation;
};

}}}

#endif
