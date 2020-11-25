#pragma once
#include "Component.h"
#include "InputManager.h"
class CameraController :
	public Component
{
private:
	const float cMoveSpeed;
	const float cRotSpeed;

	void HandleMovement(float deltaTime);
	void HandleRotation(float deltaTime);

public:
	CameraController();

	virtual void Update(float deltaTime);
};

