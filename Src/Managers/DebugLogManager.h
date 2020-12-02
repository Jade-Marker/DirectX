#pragma once
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <windows.h>
#include "Constants.h"

class DebugStream :std::ostream
{
private:
	void Output(std::string message);

public:
	DebugStream();

	template<typename T>
	DebugStream& operator<<(const T& value);
	DebugStream& operator<<(const char* value);
	DebugStream& operator<<(const std::string value);
};

class DebugLogManager
{
private:
	std::ofstream _debugLog;
	DebugStream _debugStream;

	DebugLogManager();
	~DebugLogManager();

	static DebugLogManager* GetInstance();

	friend class DebugStream;

public:
	static void Initialise();
	static void Log(std::string message);
	static void Clear();

	static DebugStream& GetStream();
};

template<typename T>
DebugStream& DebugStream::operator<<(const T& value)
{
	Output(std::to_string(value));
	return *this;
}
