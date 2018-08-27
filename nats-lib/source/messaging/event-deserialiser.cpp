#include "event-deserialiser.h"

#include <messaging/events/connect-event.h>
#include <messaging/events/info-event.h>

#include <algorithm>
#include <iostream>

using namespace synonms::nats::messaging::events;
using namespace synonms::nats::json;
using namespace synonms::nats::logging;
using namespace synonms::nats::messaging;

class EventDeserialiser::Implementation
{
public:
	Implementation(std::shared_ptr<logging::ILogger> logger, std::shared_ptr<json::IJsonObjectFactory> jsonObjectFactory)
		: logger(logger)
		, jsonObjectFactory(jsonObjectFactory)
	{
	}

	std::shared_ptr<logging::ILogger> logger;
	std::shared_ptr<json::IJsonObjectFactory> jsonObjectFactory;

	std::unique_ptr<events::Event> deserialiseConnect(const std::string& json)
	{
		auto jsonObject = jsonObjectFactory->create();

		jsonObject->update(json);

		events::ConnectEvent message;
		message.verbose = jsonObject->valueAsBool("verbose");
		message.pedantic = jsonObject->valueAsBool("pedantic");
		message.ssl_required = jsonObject->valueAsBool("ssl_required");
		message.auth_token = jsonObject->valueAsString("auth_token");
		message.user = jsonObject->valueAsString("user");
		message.pass = jsonObject->valueAsString("pass");
		message.name = jsonObject->valueAsString("name");
		message.lang = jsonObject->valueAsString("lang");
		message.version = jsonObject->valueAsString("version");
		message.protocol = jsonObject->valueAsInt32("protocol");
		message.echo = jsonObject->valueAsBool("echo");

		return std::make_unique<events::ConnectEvent>(message);
	}

	std::unique_ptr<events::Event> deserialiseInfo(const std::string& json)
	{
		auto jsonObject = jsonObjectFactory->create();

		jsonObject->update(json);

		events::InfoEvent message;
		message.server_id = jsonObject->valueAsString("server_id");
		message.version = jsonObject->valueAsString("version");
		message.git_commit = jsonObject->valueAsString("git_commit");
		message.go = jsonObject->valueAsString("go");
		message.host = jsonObject->valueAsString("host");
		message.port = jsonObject->valueAsInt32("port");
		message.auth_required = jsonObject->valueAsBool("auth_required");
		message.tls_required = jsonObject->valueAsBool("tls_required");
		message.tls_verify = jsonObject->valueAsBool("tls_verify");
		message.max_payload = jsonObject->valueAsInt64("max_payload");

		return std::make_unique<events::InfoEvent>(message);
	}
};

EventDeserialiser::EventDeserialiser(std::shared_ptr<logging::ILogger> logger, std::shared_ptr<IJsonObjectFactory> jsonObjectFactory)
{
	implementation.reset(new Implementation(logger, jsonObjectFactory));
}

EventDeserialiser::~EventDeserialiser() = default;

std::unique_ptr<Event> EventDeserialiser::deserialise(const std::string& data)
{
	auto spaceIndex = data.find_first_of(" {");

	if (spaceIndex <= 0)
	{
		implementation->logger->error("Unable to find space in message", LOG_DEFAULTS);
		return nullptr;
	}

	auto messageType = data.substr(0, spaceIndex);

	if(messageType == "CONNECT") return implementation->deserialiseConnect(data.substr(spaceIndex));
	if(messageType == "INFO") return implementation->deserialiseInfo(data.substr(spaceIndex));

	implementation->logger->error("Unable to find deserialiser for message type '" + messageType + "'", LOG_DEFAULTS);
	return nullptr;
}
