#pragma once
#include "Structures.h"

class Camera
{
private:
	Transform _transform;

	float _windowWidth;
	float _windowHeight;
	float _nearDepth;
	float _farDepth;

	XMFLOAT4X4 _view;
	XMFLOAT4X4 _projection;

	void UpdateView();
	void UpdateProjection();

public:
	Camera(const Transform& transform,
		float windowWidth, float windowHeight, float nearDepth, float farDepth);

	const XMFLOAT3& GetPosition();
	const XMFLOAT3& GetDirection();
	const XMFLOAT3& GetUp();

	const XMFLOAT4X4& GetViewMatrix();
	const XMFLOAT4X4& GetProjectionMatrix();

	void Reshape(float windowWidth, float windowHeight, float nearDepth, float farDepth);
	void Reshape(float windowWidth, float windowHeight);
};

