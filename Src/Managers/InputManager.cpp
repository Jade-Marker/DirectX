#include "InputManager.h"

InputManager::InputManager():
	_keysHeld{false}, _keysDown{false}
{
}

InputManager::~InputManager()
{
}

InputManager* InputManager::GetInstance()
{
	static InputManager instance;

	return &instance;
}

void InputManager::KeyDown(unsigned char key)
{
	InputManager* instance = GetInstance();

	if (!instance->_keysHeld[key])
	{
		instance->_keysHeld[key] = true;
		instance->_keysDown[key] = true;
	}
}

void InputManager::KeyUp(unsigned char key)
{
	InputManager* instance = GetInstance();

	instance->_keysHeld[key] = false;
}

bool InputManager::GetKey(unsigned char key)
{
	InputManager* instance = GetInstance();

	return instance->_keysHeld[key];
}

bool InputManager::GetKeyDown(unsigned char key)
{
	InputManager* instance = GetInstance();

	return instance->_keysDown[key];
}

void InputManager::Update()
{
	InputManager* instance = GetInstance();

	for (int i = 0; i < cKeyBoardCount; i++)
	{
		if (instance->_keysDown[i])
			instance->_keysDown[i] = false;
	}
}
