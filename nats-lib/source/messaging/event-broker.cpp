#include "event-broker.h"

#include <iostream>

using namespace synonms::nats::logging;
using namespace synonms::nats::messaging;
using namespace synonms::nats::messaging::handlers;

class EventBroker::Implementation
{
public:
	Implementation(std::shared_ptr<ILogger> logger)
		: logger(logger)
	{
	}

	std::shared_ptr<ILogger> logger;
	std::vector<std::unique_ptr<IEventHandler>> handlers;
};

EventBroker::EventBroker(std::shared_ptr<ILogger> logger)
{
	implementation.reset(new Implementation(logger));
}

EventBroker::~EventBroker() = default;

void EventBroker::addHandler(std::unique_ptr<IEventHandler> handler)
{
	implementation->handlers.push_back(std::move(handler));
}

void EventBroker::delegate(events::Event* event)
{
	for(const auto& handler : implementation->handlers) {
		if(handler->type() == event->type()) {
			implementation->logger->debug("Handler found, processing event...", LOG_DEFAULTS);
			handler->process(event);
		}
	}
}

