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
	CheckResult(_lua.safe_script_file(filePath));
}

void CustomComponent::LoadLibraries()
{
	_lua.open_libraries(sol::lib::base);
	_lua.open_libraries(sol::lib::math);
}

void CustomComponent::InitUserTypes()
{
	sol::usertype<Vector3D> vector3D = _lua.new_usertype<Vector3D>(
		"Vector3D",
		sol::constructors<Vector3D(), Vector3D(float, float, float)>(),
		sol::meta_method::addition, &Vector3D::operator+,
		"x", &Vector3D::x,
		"y", &Vector3D::y,
		"z", &Vector3D::z
		);
	_lua.set_function("Vector3D", [](float x, float y, float z) {return Vector3D(x, y, z); });

	Quaternion(*floatFunc)(float, float, float) = &Quaternion::EulerToQuaternion;
	sol::usertype<Quaternion> quaternion = _lua.new_usertype<Quaternion>(
		"Quaternion",
		"x", &Quaternion::x,
		"y", &Quaternion::y,
		"z", &Quaternion::z,
		"w", &Quaternion::w,
		"EulerToQuaternion", floatFunc,
		"ToEuler", &Quaternion::ToEuler
		);

	sol::usertype<Transform> transform = _lua.new_usertype<Transform>(
		"Transform",
		"Position", &Transform::Position,
		"Rotation", &Transform::Rotation,
		"Scale", &Transform::Scale,
		"Rotate", &Transform::EulerRotate,
		"Translate", &Transform::Translate
		);

	sol::usertype<Component> component = _lua.new_usertype<Component>(
		"Component"
		);

	sol::usertype<Camera> camera = _lua.new_usertype<Camera>(
		"Camera",
		sol::base_classes, sol::bases<Component>()
		);

	sol::usertype<CustomComponent> customComponent = _lua.new_usertype<CustomComponent>(
		"CustomComponent",
		"GetFunction", &CustomComponent::GetLuaFunction,
		sol::base_classes, sol::bases<Component>()
		);

	sol::usertype<Entity> entity = _lua.new_usertype<Entity>(
		"Entity",
		"GetParent", &Entity::GetParent,
		"GetTransform", &Entity::GetTransform
		);
}

void CustomComponent::SetFunctions()
{
	_lua.set_function("Log", DebugLogManager::Log);
	_lua.set_function("GetComponent", &CustomComponent::GetComponent);
	_lua.set_function("GetEntityComponent", &CustomComponent::GetEntityComponent);
	_lua.set_function("SetMainCamera", CameraManager::SetMainCamera);
	_lua.set_function("GetMainCamera", CameraManager::GetMainCamera);
	_lua.set_function("GetKeyDown", InputManager::GetKeyDown);
	_lua.set_function("GetKey", InputManager::GetKey);
	_lua.set_function("GetDeltaMousePos", CustomComponent::GetDeltaMousePos);
}

void CustomComponent::GetFunctions()
{
	_startFunction = _lua["Start"];
	_updateFunction = _lua["Update"];
	_drawFunction = _lua["Draw"];
	_onSelectedFunction = _lua["OnSelected"];
}

void CustomComponent::InitVariables()
{
	_lua.set("InitialTransform", _pParent->GetTransform());
	_lua.set("Transform", &_pParent->GetTransform());

	_lua["ComponentType"] = _lua.create_table_with(
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

	//With more time, this section would have been fleshed out to contain all inputs
	_lua["Input"] = _lua.create_table_with(
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

	_lua.set("this", this);

	_lua.set("parent", _pParent);
}

sol::object CustomComponent::CreateObject(ComponentType type, Entity* entity)
{
	sol::object object;

	//With more time, this section would have been fleshed out so that it covered all component types
	switch (type)
	{
	case CAMERA:
		object = sol::make_object<Camera*>(_lua, (Camera*)entity->GetComponent<Camera>());
		break;

	case CUSTOM_COMPONENT:
		object = sol::make_object<CustomComponent*>(_lua, (CustomComponent*)entity->GetComponent<CustomComponent>());
		break;
	}

	return object;
}

sol::object CustomComponent::GetComponent(ComponentType type)
{
	return CreateObject(type, _pParent);
}

sol::object CustomComponent::GetEntityComponent(Entity* entity, ComponentType type)
{
	return CreateObject(type, entity);
}

sol::function CustomComponent::GetLuaFunction(std::string name)
{
	return _lua[name];
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

	SafeCall(_startFunction);
}

void CustomComponent::Draw()
{
	SafeCall(_drawFunction);
}

void CustomComponent::Update(float deltaTime)
{
	SafeCall(_updateFunction, deltaTime);
}

void CustomComponent::OnSelected()
{
	SafeCall(_onSelectedFunction);
}