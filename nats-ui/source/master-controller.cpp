#include "master-controller.h"

#include <json/qtjsonobjectfactory.h>
#include <logging/console-logger.h>
#include <messaging/event-broker.h>
#include <messaging/event-deserialiser.h>
#include <messaging/event-serialiser.h>
#include <messaging/handlers/info-event-handler.h>
#include <networking/qtsocket.h>
#include <client.h>

#include <map>
#include <memory>
#include <iostream>

using namespace synonms::nats;
using namespace synonms::nats::controllers;
using namespace synonms::nats::json;
using namespace synonms::nats::logging;
using namespace synonms::nats::messaging;
using namespace synonms::nats::messaging::handlers;
using namespace synonms::nats::networking;

class MasterController::Implementation
{
public:
	Implementation(MasterController* _masterController)
		: masterController(_masterController)
	{
		logger = std::make_shared<ConsoleLogger>(LogLevel::Debug);
		socket = std::make_shared<QtSocket>(logger);
		eventBroker = std::make_shared<EventBroker>(logger);
		jsonObjectFactory = std::make_shared<QtJsonObjectFactory>();
		eventSerialiser = std::make_shared<EventSerialiser>(logger, jsonObjectFactory);
		eventDeserialiser = std::make_shared<EventDeserialiser>(logger, jsonObjectFactory);
		eventBroker->addHandler(std::make_unique<InfoEventHandler>(logger, socket, eventSerialiser));
		client = std::make_unique<Client>(logger, socket, eventDeserialiser, eventBroker);
	}

	MasterController* masterController{nullptr};
	std::shared_ptr<ConsoleLogger> logger;
	std::unique_ptr<Client> client;
	std::shared_ptr<QtSocket> socket;
	std::shared_ptr<QtJsonObjectFactory> jsonObjectFactory;
	std::shared_ptr<EventBroker> eventBroker;
	std::shared_ptr<EventSerialiser> eventSerialiser;
	std::shared_ptr<EventDeserialiser> eventDeserialiser;
};

MasterController::MasterController(QObject* parent)
	: QObject(parent)
{
	implementation.reset(new Implementation(this));
}

MasterController::~MasterController()
{
}

void MasterController::connect()
{
	implementation->logger->debug("Connecting...", LOG_DEFAULTS);

	implementation->socket->connect("127.0.0.1", 4222);
}

void MasterController::disconnect()
{
	implementation->logger->debug("Disconnecting...", LOG_DEFAULTS);

	implementation->socket->disconnect();
}
