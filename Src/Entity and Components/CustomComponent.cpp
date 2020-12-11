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

	sol::usertype<Component> component = lua.new_usertype<Component>(
		"Component"
		);

	sol::usertype<Camera> camera = lua.new_usertype<Camera>(
		"Camera",
		sol::base_classes, sol::bases<Component>()
		);
}

void CustomComponent::SetFunctions()
{
	lua.set_function("Log", DebugLogManager::Log);
	lua.set_function("GetComponent", &CustomComponent::GetComponent);
	lua.set_function("SetMainCamera", CameraManager::SetMainCamera);
	lua.set_function("GetKeyDown", InputManager::GetKeyDown);
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

	lua["ComponentType"] = lua.create_table_with(
		"MATERIAL", MATERIAL,
		"MESH", MESH,
		"RENDERER", RENDERER,
		"RASTER_STATE", RASTER_STATE,
		"ROTATOR", ROTATOR,
		"RENDERING_BUFFER", RENDERING_BUFFER,
		"SELECTION_HIDE", SELECTION_HIDE,
		"CAMERA", CAMERA,
		"CAMERA_CONTROLLER", CAMERA_CONTROLLER,
		"SCENE_LIGHT", SCENE_LIGHT,
		"SKYBOX_RASTER_STATE", SKYBOX_RASTER_STATE,
		"CUSTOM_COMPONENT", CUSTOM_COMPONENT
	);

	lua["Input"] = lua.create_table_with(
		"KEY_1", (int)'1',
		"KEY_2", (int)'2'
	);

	lua.set("this", this);
}

sol::object CustomComponent::GetComponent(ComponentType type)
{
	sol::object component;

	switch (type)
	{
		case CAMERA:
			component = sol::make_object<Camera*>(lua, (Camera*)_parent->GetComponent<Camera>());
			break;
	}

	return component;
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