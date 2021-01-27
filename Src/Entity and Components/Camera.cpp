#include "Camera.h"

void Camera::UpdateView()
{
    _view = _pParent->GetWorldMatrix().Inverse();
}

void Camera::UpdateProjection()
{
    _projection = Matrix::PerspectiveFovLH(cPIDIV2, _windowWidth / _windowHeight, _nearDepth, _farDepth);
}

Camera::Camera(float windowWidth, float windowHeight, float nearDepth, float farDepth):
    _windowWidth(windowWidth), _windowHeight(windowHeight), _nearDepth(nearDepth), _farDepth(farDepth)
{
    
}

void Camera::Start()
{
    UpdateView();
    UpdateProjection();
}

void Camera::Update(float deltaTime)
{
    UpdateView();
}

const Vector3D& Camera::GetPosition()
{
    return _pParent->GetTransform().Position;
}

Vector3D Camera::GetForward()
{
    return _pParent->GetTransform().GetRotationMatrix() * Vector3D(0, 0, 1);
}

Vector3D Camera::GetUp()
{
    return _pParent->GetTransform().GetRotationMatrix() * Vector3D(0, 1, 0);
}

Vector3D Camera::GetRight()
{
    return _pParent->GetTransform().GetRotationMatrix() * Vector3D(1, 0, 0);
}

const Matrix& Camera::GetViewMatrix()
{
    return _view;
}

const Matrix& Camera::GetProjectionMatrix()
{
    return _projection;
}

void Camera::Reshape(float windowWidth, float windowHeight, float nearDepth, float farDepth)
{
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    _nearDepth = nearDepth;
    _farDepth = farDepth;
    UpdateProjection();
}

void Camera::Reshape(float windowWidth, float windowHeight)
{
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    UpdateProjection();
}

float Camera::GetWidth()
{
    return _windowWidth;
}

float Camera::GetHeight()
{
    return _windowHeight;
}
