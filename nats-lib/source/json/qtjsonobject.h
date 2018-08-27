#ifndef QTJSONOBJECT_H
#define QTJSONOBJECT_H

#include <json/ijsonobject.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

namespace synonms {
namespace nats {
namespace json {

class NATSLIBSHARED_EXPORT QtJsonObject : public IJsonObject
{
public:
	void clear() override { _jsonObject.erase(std::begin(_jsonObject)); }

	void insert(const std::string& key, bool value) override { _jsonObject.insert(QString(key.c_str()), value); }
	void insert(const std::string& key, const std::string& value) override { _jsonObject.insert(QString(key.c_str()), QString(value.c_str())); }
	void insert(const std::string& key, int32_t value) override { _jsonObject.insert(QString(key.c_str()), static_cast<qint32>(value)); }
	void insert(const std::string& key, int64_t value) override { _jsonObject.insert(QString(key.c_str()), static_cast<qint64>(value)); }
	void insert(const std::string& key, double value) override { _jsonObject.insert(QString(key.c_str()), value); }

	void update(const std::string& json) override { _jsonObject = QJsonDocument::fromRawData(json.c_str(), static_cast<int>(json.size())).object(); }

	bool valueAsBool(const std::string& key) override { return _jsonObject.value(QString(key.c_str())).toBool(); }
	std::string valueAsString(const std::string& key) override { return _jsonObject.value(QString(key.c_str())).toString().toStdString(); }
	int32_t valueAsInt32(const std::string& key) override { return _jsonObject.value(QString(key.c_str())).toInt(); }
	int64_t valueAsInt64(const std::string& key) override { return _jsonObject.value(QString(key.c_str())).toInt(); } // TODO - No 64 support in QJsonValue??
	double valueAsDouble(const std::string& key) override { return _jsonObject.value(QString(key.c_str())).toDouble(); }

	std::string toString() override { return std::string( QJsonDocument(_jsonObject).toJson(QJsonDocument::Compact).data() ); }

private:
	QJsonObject _jsonObject;
};

}}}

#endif
