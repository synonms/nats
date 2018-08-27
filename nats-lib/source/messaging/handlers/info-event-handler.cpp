#include "info-event-handler.h"

#include <messaging/events/connect-event.h>

#include <iostream>

using namespace synonms::nats::logging;
using namespace synonms::nats::messaging::events;
using namespace synonms::nats::messaging::handlers;
using namespace synonms::nats::networking;

class InfoEventHandler::Implementation
{
public:
	Implementation(std::shared_ptr<ILogger> logger, std::shared_ptr<ISocket> socket, std::shared_ptr<IEventSerialiser> eventSerialiser)
		: logger(logger)
		, socket(socket)
		, eventSerialiser(eventSerialiser)
	{}

	std::shared_ptr<ILogger> logger;
	std::shared_ptr<ISocket> socket;
	std::shared_ptr<IEventSerialiser> eventSerialiser;
};

InfoEventHandler::InfoEventHandler(std::shared_ptr<ILogger> logger, std::shared_ptr<ISocket> socket, std::shared_ptr<IEventSerialiser> eventSerialiser)
{
	implementation.reset(new Implementation(logger, socket, eventSerialiser));
}

InfoEventHandler::~InfoEventHandler() = default;

EventType InfoEventHandler::type() const
{
	return EventType::Info;
}

void InfoEventHandler::process(Event* /*event*/)
{
	implementation->logger->debug("Processing INFO message", LOG_DEFAULTS);

	ConnectEvent connectMessage;
	connectMessage.auth_token = "";
	connectMessage.user = "";
	connectMessage.pass = "";
	connectMessage.name = "synonms-nats";
	connectMessage.lang = "cpp";
	connectMessage.version = "1.0.0";
	connectMessage.protocol = 0;
	connectMessage.verbose = false;
	connectMessage.pedantic = false;
	connectMessage.ssl_required = false;
	connectMessage.echo = false;

	implementation->socket->send(implementation->eventSerialiser->serialise(&connectMessage));
}
