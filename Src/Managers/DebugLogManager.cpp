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

void DebugLogManager::Log(std::string message)
{
	DebugLogManager* instance = GetInstance();

	std::time_t currentTime = std::time(nullptr);
	std::tm time;
	localtime_s(&time, &currentTime);

	instance->_debugLog << "[" << std::put_time(&time, "%H:%M:%S") << "]"<< message << std::endl;
}

void DebugLogManager::Clear()
{
	DebugLogManager* instance = GetInstance();

	instance->_debugLog.close();
	instance->_debugLog.open(cLogPath, std::ios::trunc);

}
