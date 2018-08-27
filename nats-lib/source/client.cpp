#include "client.h"

#include <iostream>

#include <json/qtjsonobjectfactory.h>
#include <messaging/event-broker.h>

using namespace synonms::nats;
using namespace synonms::nats::json;
using namespace synonms::nats::logging;
using namespace synonms::nats::messaging;
using namespace synonms::nats::networking;

class Client::Implementation
{
public:
	Implementation(std::shared_ptr<ILogger> logger, std::shared_ptr<ISocket> socket, std::shared_ptr<IEventDeserialiser> eventDeserialiser, std::shared_ptr<IEventBroker> eventBroker)
		: logger(logger)
		, socket(socket)
		, eventDeserialiser(eventDeserialiser)
		, eventBroker(eventBroker)
	{
		connectSlots();
	}

	std::shared_ptr<ILogger> logger;
	std::shared_ptr<ISocket> socket;
	std::shared_ptr<IEventDeserialiser> eventDeserialiser;
	std::shared_ptr<IEventBroker> eventBroker;

	void connectSlots()
	{
		socket->ConnectedEventHandlers.push_back([=](){
			logger->checkpoint("CONNECTED!!!", LOG_DEFAULTS);
		});

		socket->DisconnectedEventHandlers.push_back([=](){
			logger->checkpoint("DISCONNECTED!!!", LOG_DEFAULTS);
		});

		socket->SocketErrorEventHandlers.push_back([=](std::string error){
			logger->error("Connection Error: " + error, LOG_DEFAULTS);;
		});

		socket->SslErrorEventHandlers.push_back([=](std::vector<std::string> errors){
			logger->error("SSL Errors:", LOG_DEFAULTS);
			for(const auto& error : errors) logger->error(error, LOG_DEFAULTS);
		});

		socket->ReadyReadEventHandlers.push_back([=](std::string data){
			auto event = eventDeserialiser->deserialise(data);
			if(event == nullptr) {
				logger->error("Unable to deserialise data '" + data + "'", LOG_DEFAULTS);
				return;
			}
			logger->debug("Delegating event...", LOG_DEFAULTS);
			eventBroker->delegate(event.get());
		});
	}
};

Client::Client(std::shared_ptr<ILogger> logger, std::shared_ptr<ISocket> socket, std::shared_ptr<IEventDeserialiser> eventDeserialiser, std::shared_ptr<IEventBroker> eventBroker)
{
	implementation.reset(new Implementation(logger, socket, eventDeserialiser, eventBroker));
}

Client::~Client() = default;
