#include "DebugCameraController.h"

void DebugCameraController::HandleMovement(float deltaTime)
{
	Vector3D offset = Vector3D();

	bool isRunning = InputManager::GetKey(VK_SHIFT);

	if (InputManager::GetKey('W'))
	{
		offset += CameraManager::GetMainCamera()->GetForward();
	}

	if (InputManager::GetKey('S'))
	{
		offset -= CameraManager::GetMainCamera()->GetForward();
	}

	if (InputManager::GetKey('A'))
	{
		offset -= CameraManager::GetMainCamera()->GetRight();
	}

	if (InputManager::GetKey('D'))
	{
		offset += CameraManager::GetMainCamera()->GetRight();
	}


	offset.Normalise();
	offset *= cMoveSpeed;
	offset *= deltaTime;

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
		_pParent->GetTransform().Rotate(Vector3D(float(deltaY), float(deltaX), 0) * cRotSpeed);
	}
}

void DebugCameraController::HandleSelection()
{
	if (InputManager::GetKeyDown(VK_LBUTTON))
	{
		std::vector<Entity*> entities = EntityManager::GetEntities();
		Entity* selectedObject = nullptr;
		float smallestDistance = std::numeric_limits<float>::infinity();
		Vector3D cameraPosition = CameraManager::GetMainCamera()->GetPosition();
		Vector3D cameraDirection = CameraManager::GetMainCamera()->GetForward();
		DirectX::XMVECTOR rayOrigin = DirectX::XMVectorSet(cameraPosition.x, cameraPosition.y, cameraPosition.z, 1.0f);
		DirectX::XMVECTOR rayDirection = DirectX::XMVectorSet(cameraDirection.x, cameraDirection.y, cameraDirection.z, 1.0f);

		for (int i = 0; i < entities.size(); i++)
		{
			Mesh* pMesh = entities[i]->GetComponent<Mesh>();
			if (pMesh && entities[i]->IsSelectable())
			{
				Vector3D boundingCenter = pMesh->GetBoundingCenter();
				Vector3D boundingSize = pMesh->GetBoundingSize();

				DirectX::BoundingBox boundingBox = DirectX::BoundingBox(DirectX::XMFLOAT3(boundingCenter.x, boundingCenter.y, boundingCenter.z), DirectX::XMFLOAT3(boundingSize.x, boundingSize.y, boundingSize.z));
				DirectX::XMMATRIX worldMatrix = DirectX::XMMATRIX(entities[i]->GetWorldMatrix().values);
				worldMatrix = DirectX::XMMatrixTranspose(worldMatrix);
				boundingBox.Transform(boundingBox, worldMatrix);

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
	cMoveSpeed(20.0f), cRotSpeed(0.001f), cRunningScale(4.0f)
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