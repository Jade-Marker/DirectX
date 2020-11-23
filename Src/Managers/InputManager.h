#pragma once

#include <windows.h>
#include "CameraManager.h"

class InputManager
{
private:
	static const int cKeyBoardCount = 256;

	bool _keysHeld[cKeyBoardCount];
	bool _keysDown[cKeyBoardCount];
	int _mouseX, _mouseY;
	int _deltaMouseX, _deltaMouseY;
	bool _hasFocus;
	int _windowX, _windowY;

	InputManager();
	~InputManager();
	static InputManager* GetInstance();	

public:
	static void KeyDown(unsigned char key);
	static void KeyUp(unsigned char key);
	static void MouseMove(int x, int y);
	static void FocusChange(bool hasFocus);
	static void WindowMove(int x, int y);

	static bool GetKey(unsigned char key);
	static bool GetKeyDown(unsigned char key);
	static void GetMousePos(int& x, int& y);
	static void GetDeltaMousePos(int& deltaX, int& deltaY);
	static void Update();
	static void Initialise();
};

