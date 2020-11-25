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

void InputManager::MouseMove(int x, int y)
{
	InputManager* instance = GetInstance();
	
	if (instance->_hasFocus)
	{
		instance->_deltaMouseX = x - (int)(CameraManager::GetMainCamera()->GetWidth() / 2.0f);
		instance->_deltaMouseY = y - (int)(CameraManager::GetMainCamera()->GetHeight() / 2.0f);

		instance->_mouseX = x;
		instance->_mouseY = y;

		SetCursorPos((int)(CameraManager::GetMainCamera()->GetWidth() / 2.0f) + instance->_windowX, (int)(CameraManager::GetMainCamera()->GetHeight() / 2.0f) + instance->_windowY);
	}
}

void InputManager::FocusChange(bool hasFocus)
{
	InputManager* instance = GetInstance();
	instance->_hasFocus = hasFocus;
}

void InputManager::WindowMove(int x, int y)
{
	InputManager* instance = GetInstance();

	instance->_windowX = x;
	instance->_windowY = y;
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

void InputManager::GetMousePos(int& x, int& y)
{
	InputManager* instance = GetInstance();
	
	x = instance->_mouseX;
	y = instance->_mouseY;
}

void InputManager::GetDeltaMousePos(int& deltaX, int& deltaY)
{
	InputManager* instance = GetInstance();

	deltaX = instance->_deltaMouseX;
	deltaY = instance->_deltaMouseY;
}

void InputManager::Update()
{
	InputManager* instance = GetInstance();

	for (int i = 0; i < cKeyBoardCount; i++)
	{
		if (instance->_keysDown[i])
			instance->_keysDown[i] = false;
	}

	instance->_deltaMouseX = 0;
	instance->_deltaMouseY = 0;
}

void InputManager::Initialise()
{
	ShowCursor(false);
}
