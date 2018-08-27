#ifndef LOGLEVEL_H
#define LOGLEVEL_H

#include <cstdint>
#include <string>

namespace synonms {
namespace nats {
namespace logging {

enum class LogLevel : uint32_t
{
	Debug = 0,
	Info = 1,
	Warn = 2,
	Error = 3,
	Fatal = 4
};

class LogLevelMapper
{
public:
	static LogLevel	fromValue(uint32_t value)
	{
		switch(value)
		{
		case 0: return LogLevel::Debug;
		case 1: return LogLevel::Info;
		case 2: return LogLevel::Warn;
		case 3: return LogLevel::Error;
		case 4: return LogLevel::Fatal;
		default: return LogLevel::Warn;
		}
	}

	static LogLevel fromString(const std::string& value)
	{
		if (value == "debug") return LogLevel::Debug;
		if (value == "info") return LogLevel::Info;
		if (value == "warn") return LogLevel::Warn;
		if (value == "error") return LogLevel::Error;
		if (value == "fatal") return LogLevel::Fatal;
		return LogLevel::Warn;
	}

	static std::string toString(LogLevel value)
	{
		switch(value)
		{
		case LogLevel::Debug: return "debug";
		case LogLevel::Info: return "info";
		case LogLevel::Warn: return "warn";
		case LogLevel::Error: return "error";
		case LogLevel::Fatal: return "fatal";
		default: return "warn";
		}
	}

private:
	LogLevelMapper() = default;
};

}}}

#endif
