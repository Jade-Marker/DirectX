#pragma once
#include <DirectXMath.h>
#include "Component.h"
#include "InputManager.h"

using namespace DirectX;

class Rotator :
	public Component
{
private:
	XMFLOAT3 _tScale;
	bool _yDirState;
	bool _xDirState;

public:
	Rotator(XMFLOAT3 tScale);
	virtual void Update(float deltaTime);
};

