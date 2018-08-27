#include "event-serialiser.h"

#include <json/ijsonobjectfactory.h>
#include <messaging/i-event-serialiser.h>
#include <nats-lib_global.h>

#include <messaging/events/connect-event.h>
#include <messaging/events/info-event.h>

using namespace synonms::nats::json;
using namespace synonms::nats::logging;
using namespace synonms::nats::messaging;
using namespace synonms::nats::messaging::events;

class EventSerialiser::Implementation
{
public:
	Implementation(std::shared_ptr<ILogger> logger, std::shared_ptr<IJsonObjectFactory> jsonObjectFactory)
		: logger(logger)
		, jsonObjectFactory(jsonObjectFactory)
	{
	}

	std::shared_ptr<ILogger> logger;
	std::shared_ptr<IJsonObjectFactory> jsonObjectFactory;

	std::string serialiseConnectEvent(events::ConnectEvent& event)
	{
		auto jsonObject = jsonObjectFactory->create();

		jsonObject->insert("verbose", event.verbose);
		jsonObject->insert("pedantic", event.pedantic);
		jsonObject->insert("ssl_required", event.ssl_required);
		jsonObject->insert("auth_token", event.auth_token);
		jsonObject->insert("user", event.user);
		jsonObject->insert("pass", event.pass);
		jsonObject->insert("name", event.name);
		jsonObject->insert("lang", event.lang);
		jsonObject->insert("version", event.version);
		jsonObject->insert("protocol", event.protocol);
		jsonObject->insert("echo", event.echo);

		return "CONNECT " + jsonObject->toString() + "\r\n";
	}

	std::string serialiseInfoEvent(events::InfoEvent& event)
	{
		auto jsonObject = jsonObjectFactory->create();

		jsonObject->insert("server_id", event.server_id);
		jsonObject->insert("version", event.version);
		jsonObject->insert("git_commit", event.git_commit);
		jsonObject->insert("go", event.go);
		jsonObject->insert("host", event.host);
		jsonObject->insert("port", event.port);
		jsonObject->insert("auth_required", event.auth_required);
		jsonObject->insert("tls_required", event.tls_required);
		jsonObject->insert("tls_verify", event.tls_verify);
		jsonObject->insert("max_payload", event.max_payload);

		return "INFO " + jsonObject->toString() + "\r\n";
	}
};

EventSerialiser::EventSerialiser(std::shared_ptr<ILogger> logger, std::shared_ptr<IJsonObjectFactory> jsonObjectFactory)
{
	implementation.reset(new Implementation(logger, jsonObjectFactory));
}

EventSerialiser::~EventSerialiser() = default;

std::string EventSerialiser::serialise(Event* event)
{
	auto connectEvent = dynamic_cast<ConnectEvent*>(event);
	if(connectEvent != nullptr) return implementation->serialiseConnectEvent(*connectEvent);

	auto infoEvent = dynamic_cast<InfoEvent*>(event);
	if(infoEvent != nullptr) return implementation->serialiseInfoEvent(*infoEvent);

	return "";
}
