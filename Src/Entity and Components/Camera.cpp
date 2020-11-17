#include "Camera.h"

void Camera::UpdateView()
{
    XMStoreFloat4x4(&_view, XMMatrixInverse(nullptr, _transform.GetWorldMatrix()));
}

void Camera::UpdateProjection()
{
    XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _windowWidth / _windowHeight, _nearDepth, _farDepth));
}

Camera::Camera(const Transform& transform, float windowWidth, float windowHeight, float nearDepth, float farDepth):
    _transform(transform), _windowWidth(windowWidth), _windowHeight(windowHeight), _nearDepth(nearDepth), _farDepth(farDepth)
{
    UpdateView();
    UpdateProjection();
}

const XMFLOAT3& Camera::GetPosition()
{
    return _transform.Position;
}

const XMFLOAT3& Camera::GetDirection()
{
    XMFLOAT3 direction = XMFLOAT3(0, 0, 1);
    XMVECTOR directionVec = XMLoadFloat3(&direction);

    directionVec = XMVector3Transform(directionVec, _transform.GetRotationMatrix());

    XMStoreFloat3(&direction, directionVec);

    return direction;
}

const XMFLOAT3& Camera::GetUp()
{
    XMFLOAT3 up = XMFLOAT3(0, 1, 0);
    XMVECTOR upVec = XMLoadFloat3(&up);

    upVec = XMVector3Transform(upVec, _transform.GetRotationMatrix());

    XMStoreFloat3(&up, upVec);

    return up;
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

void Camera::Reshape(float windowWidth, float windowHeight)
{
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    UpdateProjection();
}
