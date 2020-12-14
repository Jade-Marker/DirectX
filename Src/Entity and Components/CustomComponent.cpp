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

	sol::usertype<CustomComponent> customComponent = lua.new_usertype<CustomComponent>(
		"CustomComponent",
		"GetFunction", &CustomComponent::GetLuaFunction,
		sol::base_classes, sol::bases<Component>()
		);

	sol::usertype<Entity> entity = lua.new_usertype<Entity>(
		"Entity",
		"GetParent", &Entity::GetParent,
		"GetTransform", &Entity::GetTransform
		);
}

void CustomComponent::SetFunctions()
{
	lua.set_function("Log", DebugLogManager::Log);
	lua.set_function("GetComponent", &CustomComponent::GetComponent);
	lua.set_function("GetEntityComponent", &CustomComponent::GetEntityComponent);
	lua.set_function("SetMainCamera", CameraManager::SetMainCamera);
	lua.set_function("GetMainCamera", CameraManager::GetMainCamera);
	lua.set_function("GetKeyDown", InputManager::GetKeyDown);
	lua.set_function("GetKey", InputManager::GetKey);
	lua.set_function("GetDeltaMousePos", CustomComponent::GetDeltaMousePos);
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
		"DEBUG_CAMERA_CONTROLLER", DEBUG_CAMERA_CONTROLLER,
		"SCENE_LIGHT", SCENE_LIGHT,
		"SKYBOX_RASTER_STATE", SKYBOX_RASTER_STATE,
		"CUSTOM_COMPONENT", CUSTOM_COMPONENT
	);

	lua["Input"] = lua.create_table_with(
		"KEY_SHIFT", (int)VK_SHIFT,
		"KEY_CONTROL", (int)VK_CONTROL,

		"KEY_1", (int)'1',
		"KEY_2", (int)'2',
		"KEY_3", (int)'3',
		"KEY_4", (int)'4',
		"KEY_5", (int)'5',

		"KEY_A", (int)'A',
		"KEY_D", (int)'D',
		"KEY_S", (int)'S',
		"KEY_W", (int)'W'
	);

	lua.set("this", this);

	lua.set("parent", _parent);
}

sol::object CustomComponent::CreateObject(ComponentType type, Entity* entity)
{
	sol::object object;

	switch (type)
	{
	case CAMERA:
		object = sol::make_object<Camera*>(lua, (Camera*)entity->GetComponent<Camera>());
		break;

	case CUSTOM_COMPONENT:
		object = sol::make_object<CustomComponent*>(lua, (CustomComponent*)entity->GetComponent<CustomComponent>());
		break;
	}

	return object;
}

sol::object CustomComponent::GetComponent(ComponentType type)
{
	return CreateObject(type, _parent);
}

sol::object CustomComponent::GetEntityComponent(Entity* entity, ComponentType type)
{
	return CreateObject(type, entity);
}

sol::function CustomComponent::GetLuaFunction(std::string name)
{
	return lua[name];
}

std::tuple<int, int> CustomComponent::GetDeltaMousePos()
{
	int deltaX, deltaY;

	InputManager::GetDeltaMousePos(deltaX, deltaY);

	return std::tuple<int, int>(deltaX, deltaY);
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