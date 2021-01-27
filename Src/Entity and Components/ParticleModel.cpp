#include "ParticleModel.h"

ParticleModel::ParticleModel()
{
}

ParticleModel::ParticleModel(const Vector3D& velocity, const Vector3D& acceleration, const Vector3D& angularVelocity, const Vector3D& angularAcceleration):
	_velocity(velocity), _acceleration(acceleration), _angularVelocity(angularVelocity), _angularAcceleration(angularAcceleration)
{
}

void ParticleModel::Update(float deltaTime)
{
	_velocity += _acceleration * deltaTime;
	_pParent->GetTransform().Translate(_velocity * deltaTime);

	_angularVelocity += _angularAcceleration * deltaTime;
	_pParent->GetTransform().Rotate(_angularVelocity * deltaTime);
}
