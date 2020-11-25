#include "CameraController.h"

void CameraController::HandleMovement(float deltaTime)
{
	XMVECTOR offset = XMVectorSet(0, 0, 0, 0);

	if (InputManager::GetKey('W'))
	{
		XMFLOAT3 cameraForward = CameraManager::GetMainCamera()->GetDirection();
		offset += XMLoadFloat3(&cameraForward) * deltaTime;
	}

	if (InputManager::GetKey('S'))
	{
		XMFLOAT3 cameraForward = CameraManager::GetMainCamera()->GetDirection();
		offset += -XMLoadFloat3(&cameraForward) * deltaTime;
	}

	if (InputManager::GetKey('A'))
	{
		XMFLOAT3 cameraRight = CameraManager::GetMainCamera()->GetRight();
		offset += -XMLoadFloat3(&cameraRight) * deltaTime;
	}

	if (InputManager::GetKey('D'))
	{
		XMFLOAT3 cameraRight = CameraManager::GetMainCamera()->GetRight();
		offset += XMLoadFloat3(&cameraRight) * deltaTime;
	}

	offset = XMVector3Normalize(offset) * cMoveSpeed;
	_parent->GetTransform().Translate(offset);
}

void CameraController::HandleRotation(float deltaTime)
{
	XMVECTOR rotation = XMVectorSet(0, 0, 0, 0);
	int deltaX, deltaY;

	InputManager::GetDeltaMousePos(deltaX, deltaY);
	if (deltaX != 0 && deltaY != 0)
	{
		rotation = XMVectorSet(float(deltaY), float(deltaX), 0, 0) * cRotSpeed;
	}
	_parent->GetTransform().Rotate(rotation);
}

CameraController::CameraController():
	cMoveSpeed(0.25f), cRotSpeed(0.001f)
{
}

void CameraController::Update(float deltaTime)
{
	HandleMovement(deltaTime);
	HandleRotation(deltaTime);
}