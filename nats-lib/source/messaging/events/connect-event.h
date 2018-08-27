#ifndef CONNECTEVENT_H
#define CONNECTEVENT_H

#include <nats-lib_global.h>
#include <messaging/events/event.h>

#include <string>
#include <sstream>

namespace synonms {
namespace nats {
namespace messaging {
namespace events {

class NATSLIBSHARED_EXPORT ConnectEvent : public Event
{
public:
	ConnectEvent();

	std::string auth_token {""};
	std::string user {""};
	std::string pass {""};
	std::string name {"synonms-nats"};
	std::string lang {"cpp"};
	std::string version {"1.0.0"};
	int32_t protocol {0};
	bool verbose {false};
	bool pedantic {false};
	bool ssl_required {false};
	bool echo {false};
};

}}}}

#endif
