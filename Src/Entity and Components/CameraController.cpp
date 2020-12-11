#include "CameraController.h"

void CameraController::HandleMovement(float deltaTime)
{
	XMVECTOR offset = XMVectorSet(0, 0, 0, 0);

	bool isRunning = InputManager::GetKey(VK_SHIFT);

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

	if (isRunning)
		offset *= cRunningScale;

	_parent->GetTransform().Translate(offset);
}

void CameraController::HandleRotation()
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

void CameraController::HandleSelection()
{
	if (InputManager::GetKeyDown(VK_LBUTTON))
	{
		std::vector<Entity*> entities = EntityManager::GetEntities();
		Entity* selectedObject = nullptr;
		float minDistance = std::numeric_limits<float>::infinity();
		XMVECTOR rayOrigin = XMLoadFloat3(&CameraManager::GetMainCamera()->GetPosition());
		XMVECTOR rayDirection = XMLoadFloat3(&CameraManager::GetMainCamera()->GetDirection());

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
					if (distance < minDistance)
					{
						minDistance = distance;
						selectedObject = entities[i];
					}
				}
			}
		}

		if (selectedObject != nullptr && selectedObject != _parent)
		{
			selectedObject->OnSelected();
		}
	}
}

CameraController::CameraController():
	cMoveSpeed(0.25f), cRotSpeed(0.001f), cRunningScale(4.0f)
{
}

void CameraController::Start()
{
	_pCamera = _parent->GetComponent<Camera>();
}

void CameraController::Update(float deltaTime)
{
	if (CameraManager::GetMainCamera() == _pCamera)
	{
		HandleMovement(deltaTime);
		HandleRotation();
		HandleSelection();
	}
}