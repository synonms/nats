#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include <logging/i-logger.h>

namespace synonms {
namespace nats {
namespace logging {

class NATSLIBSHARED_EXPORT ConsoleLogger : public ILogger
{
public:
	ConsoleLogger(LogLevel level = LogLevel::Warn);
	~ConsoleLogger() override;

	void checkpoint(const std::string& message, const std::string& file, const std::string& method, int line) override;
	void debug(const std::string& message, const std::string& file, const std::string& method, int line) override;
	void error(const std::string& message, const std::string& file, const std::string& method, int line) override;
	void error(const std::string& message, const std::exception& exception, const std::string& file, const std::string& method, int line) override;
	void fatal(const std::string& message, const std::string& file, const std::string& method, int line) override;
	void fatal(const std::string& message, const std::exception& exception, const std::string& file, const std::string& method, int line) override;
	void info(const std::string& message, const std::string& file, const std::string& method, int line) override;
	void setLevel(LogLevel level) override;
	void warn(const std::string& message, const std::string& file, const std::string& method, int line) override;

private:
	LogLevel _level;

	void writeLine(const std::string& logLevel, const std::string& message, const std::string& file, const std::string& method, int line);
};

}}}

#endif
