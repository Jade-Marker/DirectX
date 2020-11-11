#pragma once
#include <DirectXMath.h>

using namespace DirectX;
class Camera
{
private:
	XMFLOAT3 _position;
	XMFLOAT3 _direction;
	XMFLOAT3 _up;

	float _windowWidth;
	float _windowHeight;
	float _nearDepth;
	float _farDepth;

	XMFLOAT4X4 _view;
	XMFLOAT4X4 _projection;

	void UpdateView();
	void UpdateProjection();

public:
	Camera(const XMFLOAT3& position, const XMFLOAT3& direction, const XMFLOAT3& up,
		float windowWidth, float windowHeight, float nearDepth, float farDepth);

	//void Update();

	void SetPosition(const XMFLOAT3& position);
	void SetDirection(const XMFLOAT3& direction);
	void SetUp(const XMFLOAT3& up);

	const XMFLOAT3& GetPosition();
	const XMFLOAT3& GetDirection();
	const XMFLOAT3& GetUp();

	const XMFLOAT4X4& GetViewMatrix();
	const XMFLOAT4X4& GetProjectionMatrix();

	void Reshape(float windowWidth, float windowHeight, float nearDepth, float farDepth);
};

