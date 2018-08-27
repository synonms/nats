#ifndef IJSONOBJECTFACTORY_H
#define IJSONOBJECTFACTORY_H

#include <nats-lib_global.h>
#include <json/ijsonobject.h>

#include <memory>

namespace synonms {
namespace nats {
namespace json {

class NATSLIBSHARED_EXPORT IJsonObjectFactory
{
public:
	virtual ~IJsonObjectFactory() = default;

	virtual std::unique_ptr<IJsonObject> create() = 0;
};

}}}

#endif
