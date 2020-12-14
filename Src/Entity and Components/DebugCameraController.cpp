#include "DebugCameraController.h"

void DebugCameraController::HandleMovement(float deltaTime)
{
	XMVECTOR offset = XMVectorSet(0, 0, 0, 0);

	bool isRunning = InputManager::GetKey(VK_SHIFT);

	if (InputManager::GetKey('W'))
	{
		XMFLOAT3 cameraForward = CameraManager::GetMainCamera()->GetForward();
		offset += XMLoadFloat3(&cameraForward) * deltaTime;
	}

	if (InputManager::GetKey('S'))
	{
		XMFLOAT3 cameraForward = CameraManager::GetMainCamera()->GetForward();
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

	if (isRunning)
		offset *= cRunningScale;

	_pParent->GetTransform().Translate(offset);
}

void DebugCameraController::HandleRotation()
{
	int deltaX, deltaY;

	InputManager::GetDeltaMousePos(deltaX, deltaY);
	if (deltaX != 0 && deltaY != 0)
	{
		XMVECTOR rotation = XMVectorSet(float(deltaY), float(deltaX), 0, 0) * cRotSpeed;
		_pParent->GetTransform().Rotate(rotation);
	}
}

void DebugCameraController::HandleSelection()
{
	if (InputManager::GetKeyDown(VK_LBUTTON))
	{
		std::vector<Entity*> entities = EntityManager::GetEntities();
		Entity* selectedObject = nullptr;
		float smallestDistance = std::numeric_limits<float>::infinity();
		XMVECTOR rayOrigin = XMLoadFloat3(&CameraManager::GetMainCamera()->GetPosition());
		XMVECTOR rayDirection = XMLoadFloat3(&CameraManager::GetMainCamera()->GetForward());

		for (int i = 0; i < entities.size(); i++)
		{
			Mesh* pMesh = entities[i]->GetComponent<Mesh>();
			if (pMesh && entities[i]->IsSelectable())
			{
				BoundingBox boundingBox = BoundingBox(pMesh->GetBoundingCenter(), pMesh->GetBoundingSize());

				boundingBox.Transform(boundingBox, entities[i]->GetWorldMatrix());

				float distance;
				if (boundingBox.Intersects(rayOrigin, rayDirection, distance))
				{
					if (distance < smallestDistance)
					{
						smallestDistance = distance;
						selectedObject = entities[i];
					}
				}
			}
		}

		if (selectedObject != nullptr && selectedObject != _pParent)
		{
			selectedObject->OnSelected();
		}
	}
}

DebugCameraController::DebugCameraController():
	cMoveSpeed(0.25f), cRotSpeed(0.001f), cRunningScale(4.0f)
{
}

void DebugCameraController::Start()
{
	_pCamera = _pParent->GetComponent<Camera>();
}

void DebugCameraController::Update(float deltaTime)
{
	//If the camera this controls isn't the main camera, then don't move/rotate/select
	if (CameraManager::GetMainCamera() == _pCamera)
	{
		HandleMovement(deltaTime);
		HandleRotation();
		HandleSelection();
	}
}