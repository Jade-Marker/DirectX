#pragma once
#include <DirectXMath.h>

using namespace DirectX;
class Camera
{
private:
	XMFLOAT3 _cameraPos;
	XMFLOAT4X4  _view;

public:
	Camera(XMFLOAT3 position);

	const XMFLOAT4X4& GetViewMatrix();
	const XMFLOAT3& GetPosition();
};

