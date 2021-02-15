#include "Rotator.h"

Rotator::Rotator(Vector3D tScale):
	_tScale(tScale), _yDirState(false), _xDirState(false)
{
}

void Rotator::Update(float deltaTime)
{
    Vector3D rotation;

    if (_xDirState)
        rotation.x += _tScale.x * deltaTime;
    else
        rotation.x -= _tScale.x * deltaTime;

    if (_yDirState)
        rotation.y += _tScale.y * deltaTime;
    else
        rotation.y -= _tScale.y * deltaTime;

    rotation.z += _tScale.z * deltaTime;

    _pParent->GetTransform().EulerRotate(rotation);

    if (InputManager::GetKeyDown('J'))
        _xDirState = true;
    else if (InputManager::GetKeyDown('L'))
        _xDirState = false;

    if (InputManager::GetKeyDown('I'))
        _yDirState = true;
    else if (InputManager::GetKeyDown('K'))
        _yDirState = false;
}
