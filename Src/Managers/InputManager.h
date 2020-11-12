#pragma once

class InputManager
{
private:
	static const int cKeyBoardCount = 256;

	bool _keysHeld[cKeyBoardCount];
	bool _keysDown[cKeyBoardCount];

	InputManager();
	~InputManager();
	static InputManager* GetInstance();	

public:
	static void KeyDown(unsigned char key);
	static void KeyUp(unsigned char key);
	static bool GetKey(unsigned char key);
	static bool GetKeyDown(unsigned char key);

	static void Update();
};

