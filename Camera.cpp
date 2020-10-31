#include "Camera.h"

Camera::Camera(XMFLOAT3 position):
    _cameraPos(position)
{
    XMVECTOR Eye = XMVectorSet(_cameraPos.x, _cameraPos.y, _cameraPos.z, 0.0f);
    XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
    XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    XMStoreFloat4x4(&_view, XMMatrixLookAtLH(Eye, At, Up));
}

const XMFLOAT4X4& Camera::GetViewMatrix()
{
	return _view;
}

const XMFLOAT3& Camera::GetPosition()
{
    return _cameraPos;
}
