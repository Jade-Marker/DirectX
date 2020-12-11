#pragma once
#include "Component.h"
#include "InputManager.h"
#include "EntityManager.h"
#include "Mesh.h"
#include <DirectXCollision.h>
class CameraController :
	public Component
{
private:
	const float cMoveSpeed;
	const float cRotSpeed;
	const float cRunningScale;
	Camera* _pCamera;

	void HandleMovement(float deltaTime);
	void HandleRotation();
	void HandleSelection();

public:
	CameraController();

	virtual void Start();
	virtual void Update(float deltaTime);
};

