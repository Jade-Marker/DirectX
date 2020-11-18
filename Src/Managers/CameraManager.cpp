#include "CameraManager.h"

CameraManager::CameraManager() :
	_mainCamera(nullptr)
{
}

CameraManager* CameraManager::GetInstance()
{
	static CameraManager instance;

	return &instance;
}

Camera* CameraManager::GetMainCamera()
{
	CameraManager* instance = GetInstance();

	return instance->_mainCamera;
}

void CameraManager::SetMainCamera(Camera* camera)
{
	CameraManager* instance = GetInstance();

	instance->_mainCamera = camera;
}
