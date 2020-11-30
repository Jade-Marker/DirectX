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

	void HandleMovement(float deltaTime);
	void HandleRotation();
	void HandleSelection();

public:
	CameraController();

	virtual void Update(float deltaTime);
};

