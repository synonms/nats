#ifndef QTJSONOBJECTFACTORY_H
#define QTJSONOBJECTFACTORY_H

#include <nats-lib_global.h>
#include <json/ijsonobjectfactory.h>
#include <json/qtjsonobject.h>

#include <memory>

namespace synonms {
namespace nats {
namespace json {

class NATSLIBSHARED_EXPORT QtJsonObjectFactory : public IJsonObjectFactory
{
public:
	std::unique_ptr<IJsonObject> create() override
	{
		return std::make_unique<QtJsonObject>();
	}
};

}}}

#endif
