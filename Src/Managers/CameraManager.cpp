#include "CameraManager.h"

CameraManager::CameraManager() :
	_pMainCamera(nullptr)
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

	return instance->_pMainCamera;
}

void CameraManager::SetMainCamera(Camera* camera)
{
	CameraManager* instance = GetInstance();

	if(instance->_pMainCamera != nullptr)
		camera->Reshape(instance->_pMainCamera->GetWidth(), instance->_pMainCamera->GetHeight());	//Reshape as window size may have changed since the camera width/height were set

	instance->_pMainCamera = camera;
}
