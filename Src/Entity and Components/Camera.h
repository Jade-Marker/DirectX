#pragma once
#include "Structures.h"
#include "Component.h"
#include <MathLibrary\Constants.h>

class Camera : public Component
{
private:
	float _windowWidth;
	float _windowHeight;
	float _nearDepth;
	float _farDepth;

	Matrix _view;
	Matrix _projection;

	void UpdateView();
	void UpdateProjection();

public:
	Camera(float windowWidth, float windowHeight, float nearDepth, float farDepth);

	virtual void Start();
	virtual void Update(float deltaTime);

	const Vector3D& GetPosition();
	Vector3D GetForward();
	Vector3D GetUp();
	Vector3D GetRight();

	const Matrix& GetViewMatrix();
	const Matrix& GetProjectionMatrix();

	void Reshape(float windowWidth, float windowHeight, float nearDepth, float farDepth);
	void Reshape(float windowWidth, float windowHeight);

	float GetWidth();
	float GetHeight();
};

