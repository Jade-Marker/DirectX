#pragma once
#include "Camera.h"

class CameraManager
{
private:
	Camera* _mainCamera;

	CameraManager();
	static CameraManager* GetInstance();

public:
	static Camera* GetMainCamera();
	static void SetMainCamera(Camera* camera);

};

