#ifndef INFOEVENT_H
#define INFOEVENT_H

#include <nats-lib_global.h>
#include <messaging/events/event.h>

#include <iostream>
#include <string>
#include <sstream>

namespace synonms {
namespace nats {
namespace messaging {
namespace events {

class NATSLIBSHARED_EXPORT InfoEvent : public Event
{
public:
	InfoEvent();

	std::string server_id {""};
	std::string version {""};
	std::string git_commit {""};
	std::string go {""};
	std::string host {"0.0.0.0"};
	int32_t port {4222};
	int64_t max_payload {1048576};
	bool auth_required {false};
	bool tls_required {false};
	bool tls_verify {false};
};

}}}}

#endif
