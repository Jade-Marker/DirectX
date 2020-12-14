#pragma once
#include "Structures.h"
#include "Component.h"

class Camera : public Component
{
private:
	float _windowWidth;
	float _windowHeight;
	float _nearDepth;
	float _farDepth;

	XMFLOAT4X4 _view;
	XMFLOAT4X4 _projection;

	void UpdateView();
	void UpdateProjection();

public:
	Camera(float windowWidth, float windowHeight, float nearDepth, float farDepth);

	virtual void Start();
	virtual void Update(float deltaTime);

	const XMFLOAT3& GetPosition();
	XMFLOAT3 GetForward();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	const XMFLOAT4X4& GetViewMatrix();
	const XMFLOAT4X4& GetProjectionMatrix();

	void Reshape(float windowWidth, float windowHeight, float nearDepth, float farDepth);
	void Reshape(float windowWidth, float windowHeight);

	float GetWidth();
	float GetHeight();
};

