#ifndef ISOCKET_H
#define ISOCKET_H

#include <nats-lib_global.h>

namespace synonms {
namespace nats {
namespace networking {

class NATSLIBSHARED_EXPORT ISocket
{

public:
	virtual ~ISocket() = default;

	virtual void Connect(const std::string& host, uint16_t port) = 0;
	virtual void Disconnect() = 0;
};

}}}

#endif
