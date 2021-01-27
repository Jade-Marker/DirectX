#pragma once
#include "Component.h"
#include "InputManager.h"

class Rotator :
	public Component
{
private:
	Vector3D _tScale;
	bool _yDirState;
	bool _xDirState;

public:
	Rotator(Vector3D tScale);
	virtual void Update(float deltaTime);
};

