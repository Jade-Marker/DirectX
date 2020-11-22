#pragma once
#include <fstream>
#include <iomanip>
#include "Constants.h"

class DebugLogManager
{
private:
	std::ofstream _debugLog;

	DebugLogManager();
	~DebugLogManager();

	static DebugLogManager* GetInstance();
public:
	static void Log(std::string message);
	static void Clear();
};

