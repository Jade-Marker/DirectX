#pragma once
#include "Component.h"
#include "InputManager.h"
#include "EntityManager.h"
#include "Mesh.h"
#include <DirectXCollision.h>
class DebugCameraController :
	public Component
{
private:
	const float cMoveSpeed;
	const float cRotSpeed;
	const float cRunningScale;
	Camera* _pCamera;
	Vector3D angle;

	void HandleMovement(float deltaTime);
	void HandleRotation();
	void HandleSelection();

public:
	DebugCameraController();

	virtual void Start();
	virtual void Update(float deltaTime);
};

