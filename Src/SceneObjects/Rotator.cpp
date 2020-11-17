#include "Rotator.h"

Rotator::Rotator(XMFLOAT3 tScale):
	_tScale(tScale), _yDirState(false), _xDirState(false)
{
}

void Rotator::Update(float deltaTime)
{
    if (_xDirState)
        _parent->GetTransform().Rotation.x += _tScale.x * deltaTime;
    else
        _parent->GetTransform().Rotation.x -= _tScale.x * deltaTime;

    if (_yDirState)
        _parent->GetTransform().Rotation.y += _tScale.y * deltaTime;
    else
        _parent->GetTransform().Rotation.y -= _tScale.y * deltaTime;

    _parent->GetTransform().Rotation.z += _tScale.z * deltaTime;

    if (InputManager::GetKeyDown('A'))
        _xDirState = true;
    else if (InputManager::GetKeyDown('D'))
        _xDirState = false;

    if (InputManager::GetKeyDown('W'))
        _yDirState = true;
    else if (InputManager::GetKeyDown('S'))
        _yDirState = false;
}
