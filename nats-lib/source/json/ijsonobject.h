#ifndef IJSONOBJECT_H
#define IJSONOBJECT_H

#include <nats-lib_global.h>

#include <cstdint>
#include <string>

namespace synonms {
namespace nats {
namespace json {

class NATSLIBSHARED_EXPORT IJsonObject
{
public:
	virtual ~IJsonObject() = default;

	virtual void clear() = 0;

	virtual void insert(const std::string& key, bool value) = 0;
	virtual void insert(const std::string& key, const std::string& value) = 0;
	virtual void insert(const std::string& key, int32_t value) = 0;
	virtual void insert(const std::string& key, int64_t value) = 0;
	virtual void insert(const std::string& key, double value) = 0;

	virtual void update(const std::string& json) = 0;

	virtual bool valueAsBool(const std::string& key) = 0;
	virtual std::string valueAsString(const std::string& key) = 0;
	virtual int32_t valueAsInt32(const std::string& key) = 0;
	virtual int64_t valueAsInt64(const std::string& key) = 0;
	virtual double valueAsDouble(const std::string& key) = 0;

	virtual std::string toString() = 0;
};

}}}

#endif
