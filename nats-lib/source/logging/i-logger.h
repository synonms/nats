#ifndef ILOGGER_H
#define ILOGGER_H

#include <nats-lib_global.h>

#include <logging/log-level.h>

#include <string>

#include <windows.h>

#define LOG_DEFAULTS __FILE__, __FUNCTION__, __LINE__

namespace synonms {
namespace nats {
namespace logging {

class NATSLIBSHARED_EXPORT ILogger
{
public:
	virtual ~ILogger() = default;

	virtual void checkpoint(const std::string& message, const std::string& file, const std::string& method, int line) = 0;
	virtual void debug(const std::string& message, const std::string& file, const std::string& method, int line) = 0;
	virtual void error(const std::string& message, const std::string& file, const std::string& method, int line) = 0;
	virtual void error(const std::string& message, const std::exception& exception, const std::string& file, const std::string& method, int line) = 0;
	virtual void fatal(const std::string& message, const std::string& file, const std::string& method, int line) = 0;
	virtual void fatal(const std::string& message, const std::exception& exception, const std::string& file, const std::string& method, int line) = 0;
	virtual void info(const std::string& message, const std::string& file, const std::string& method, int line) = 0;
	virtual void setLevel(LogLevel level) = 0;
	virtual void warn(const std::string& message, const std::string& file, const std::string& method, int line) = 0;
};

}}}

#endif
