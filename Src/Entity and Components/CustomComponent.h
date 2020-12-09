#pragma once
#include "Component.h"
#include "DebugLogManager.h"


#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <string>
#include <iostream>

class CustomComponent :
	public Component
{
private:
	sol::state lua;

	sol::function startFunction;
	sol::function updateFunction;
	sol::function drawFunction;
	sol::function onSelectedFunction;

private:
	void CheckResult(sol::protected_function_result result);
	template<typename... types>
	void SafeCall(sol::function function, types... args);
	void InitLua(const std::string& filePath);
	void LoadLibraries();
	void InitUserTypes();
	void SetFunctions();
	void GetFunctions();
	void InitVariables();

public:
	CustomComponent(const std::string& filePath);
	virtual void Start();
	virtual void Draw();
	virtual void Update(float deltaTime);
	virtual void OnSelected();
};