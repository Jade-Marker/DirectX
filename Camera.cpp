#include "Camera.h"

void Camera::UpdateView()
{
    XMVECTOR position = XMLoadFloat3(&_position);
    XMVECTOR direction = XMLoadFloat3(&_direction);
    XMVECTOR up = XMLoadFloat3(&_up);

    XMStoreFloat4x4(&_view, XMMatrixLookAtLH(position, position + direction, up));
}

void Camera::UpdateProjection()
{
    XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _windowWidth / _windowHeight, _nearDepth, _farDepth));
}

Camera::Camera(const XMFLOAT3& position, const XMFLOAT3& direction, const XMFLOAT3& up, float windowWidth, float windowHeight, float nearDepth, float farDepth):
    _position(position), _direction(direction), _up(up), _windowWidth(windowWidth), _windowHeight(windowHeight), _nearDepth(nearDepth), _farDepth(farDepth)
{
    UpdateView();
    UpdateProjection();
}

void Camera::SetPosition(const XMFLOAT3& position)
{
    _position = position;
    UpdateView();
}

void Camera::SetDirection(const XMFLOAT3& direction)
{
    _direction = direction;
    UpdateView();
}

void Camera::SetUp(const XMFLOAT3& up)
{
    _up = up;
    UpdateView();
}

const XMFLOAT3& Camera::GetPosition()
{
    return _position;
}

const XMFLOAT3& Camera::GetDirection()
{
    return _direction;
}

const XMFLOAT3& Camera::GetUp()
{
    return _up;
}

const XMFLOAT4X4& Camera::GetViewMatrix()
{
    return _view;
}

const XMFLOAT4X4& Camera::GetProjectionMatrix()
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