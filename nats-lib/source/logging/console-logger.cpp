#include "console-logger.h"

#include <iostream>
#include <thread>

using namespace synonms::nats::logging;

ConsoleLogger::ConsoleLogger(LogLevel level)
	: _level(level)
{
}

ConsoleLogger::~ConsoleLogger() = default;

void ConsoleLogger::checkpoint(const std::string& message, const std::string& file, const std::string& method, int line)
{
	writeLine("checkpoint", message, file, method, line);
}

void ConsoleLogger::debug(const std::string& message, const std::string& file, const std::string& method, int line)
{
	if(_level <= LogLevel::Debug) writeLine(LogLevelMapper::toString(LogLevel::Debug), message, file, method, line);
}

void ConsoleLogger::error(const std::string& message, const std::string& file, const std::string& method, int line)
{
	if(_level <= LogLevel::Error) writeLine(LogLevelMapper::toString(LogLevel::Error), message, file, method, line);
}

void ConsoleLogger::error(const std::string& message, const std::exception& exception, const std::string& file, const std::string& method, int line)
{
	if(_level <= LogLevel::Error) {
		writeLine(LogLevelMapper::toString(LogLevel::Error), message, file, method, line);
		writeLine(LogLevelMapper::toString(LogLevel::Error), exception.what(), file, method, line);
	}
}

void ConsoleLogger::fatal(const std::string& message, const std::string& file, const std::string& method, int line)
{
	writeLine(LogLevelMapper::toString(LogLevel::Fatal), message, file, method, line);
}

void ConsoleLogger::fatal(const std::string& message, const std::exception& exception, const std::string& file, const std::string& method, int line)
{
	writeLine(LogLevelMapper::toString(LogLevel::Fatal), message, file, method, line);
	writeLine(LogLevelMapper::toString(LogLevel::Fatal), exception.what(), file, method, line);
}

void ConsoleLogger::info(const std::string& message, const std::string& file, const std::string& method, int line)
{
	if(_level <= LogLevel::Info) writeLine(LogLevelMapper::toString(LogLevel::Info), message, file, method, line);
}

void ConsoleLogger::setLevel(LogLevel level)
{
	_level = level;
}

void ConsoleLogger::warn(const std::string& message, const std::string& file, const std::string& method, int line)
{
	if(_level <= LogLevel::Warn) writeLine(LogLevelMapper::toString(LogLevel::Warn), message, file, method, line);
}

void ConsoleLogger::writeLine(const std::string& logLevel, const std::string& message, const std::string& file, const std::string& method, int line)
{
	std::cout << logLevel << "|" << file << "|" << method << "(" << line << ")|" << std::this_thread::get_id() << "|" << message << std::endl;
}
