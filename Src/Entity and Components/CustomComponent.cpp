#include "CustomComponent.h"

void CustomComponent::CheckResult(sol::protected_function_result result)
{
	if (!result.valid())
	{
		sol::error err = result;
		DebugLogManager::Log(std::string("Error: ") + std::string(err.what()));
	}
}

template<typename ...types>
void CustomComponent::SafeCall(sol::function function, types ...args)
{
	if (function.valid())
		CheckResult(function(args...));
}

void CustomComponent::InitLua(const std::string& filePath)
{
	CheckResult(lua.safe_script_file(filePath));
}

void CustomComponent::LoadLibraries()
{
	lua.open_libraries(sol::lib::base);
	lua.open_libraries(sol::lib::math);
}

void CustomComponent::InitUserTypes()
{
	sol::usertype<XMFLOAT3> xmfloat3 = lua.new_usertype<XMFLOAT3>(
		"XMFLOAT3",
		"x", &XMFLOAT3::x,
		"y", &XMFLOAT3::y,
		"z", &XMFLOAT3::z
		);

	sol::usertype<Transform> transform = lua.new_usertype<Transform>(
		"Transform",
		"Position", &Transform::Position,
		"Rotation", &Transform::Rotation,
		"Scale", &Transform::Scale
		);
}

void CustomComponent::SetFunctions()
{
	lua.set_function("Log", DebugLogManager::Log);
}

void CustomComponent::GetFunctions()
{
	startFunction = lua["Start"];
	updateFunction = lua["Update"];
	drawFunction = lua["Draw"];
	onSelectedFunction = lua["OnSelected"];
}

void CustomComponent::InitVariables()
{
	lua.set("InitialTransform", _parent->GetTransform());
	lua.set("Transform", &_parent->GetTransform());
}

CustomComponent::CustomComponent(const std::string& filePath)
{
	LoadLibraries();
	InitUserTypes();
	InitLua(filePath);
	SetFunctions();
	GetFunctions();
}

void CustomComponent::Start()
{
	InitVariables();

	SafeCall(startFunction);
}

void CustomComponent::Draw()
{
	SafeCall(drawFunction);
}

void CustomComponent::Update(float deltaTime)
{
	SafeCall(updateFunction, deltaTime);
}

void CustomComponent::OnSelected()
{
	SafeCall(onSelectedFunction);
}
