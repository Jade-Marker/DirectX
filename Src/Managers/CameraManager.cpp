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

	if(instance->_mainCamera != nullptr)
		camera->Reshape(instance->_mainCamera->GetWidth(), instance->_mainCamera->GetHeight());

	instance->_mainCamera = camera;
}
