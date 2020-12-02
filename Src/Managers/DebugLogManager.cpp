#include "DebugLogManager.h"

DebugLogManager::DebugLogManager()
{
	_debugLog.open(cLogPath);
}

DebugLogManager::~DebugLogManager()
{
	_debugLog.close();
}

DebugLogManager* DebugLogManager::GetInstance()
{
	static DebugLogManager instance;

	return &instance;
}

void DebugLogManager::Initialise()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
}

void DebugLogManager::Log(std::string message)
{
	DebugLogManager* instance = GetInstance();

	std::time_t currentTime = std::time(nullptr);
	std::tm time;
	localtime_s(&time, &currentTime);

	std::stringstream formattedMessage;
	formattedMessage << "[" << std::put_time(&time, "%H:%M:%S") << "]" << message << std::endl;

	instance->_debugLog << formattedMessage.str();
	std::cout << formattedMessage.str();
}

void DebugLogManager::Clear()
{
	DebugLogManager* instance = GetInstance();

	instance->_debugLog.close();
	instance->_debugLog.open(cLogPath, std::ios::trunc);
}

DebugStream& DebugLogManager::GetStream()
{
	DebugLogManager* instance = DebugLogManager::GetInstance();

	return instance->_debugStream;
}

void DebugStream::Output(std::string message)
{
	DebugLogManager* instance = DebugLogManager::GetInstance();

	instance->Log(message);
}

DebugStream::DebugStream():
	std::ostream(nullptr)
{
}

DebugStream& DebugStream::operator<<(const char* value)
{
	Output(value);
	return *this;
}

DebugStream& DebugStream::operator<<(const std::string value)
{
	Output(value);
	return *this;
}