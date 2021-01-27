#pragma once
#include "Component.h"
class ParticleModel :
	public Component
{
private:
	Vector3D _velocity;
	Vector3D _acceleration;
	Vector3D _angularVelocity;
	Vector3D _angularAcceleration;

public:
	ParticleModel();
	ParticleModel(const Vector3D& velocity, const Vector3D& acceleration, const Vector3D& angularVelocity, const Vector3D& angularAcceleration);

	virtual void Update(float deltaTime);
};

