#include "Cube.h"

Cube::Cube(float x, float y, float z, float xAngle, float yAngle, float zAngle, float tX, float tY, float tZ,
    ID3D11DeviceContext* pImmediateContext, D3D_DRIVER_TYPE driverType, ID3D11VertexShader* pVertexShader, ID3D11PixelShader* pPixelShader, ID3D11Buffer* pConstantBuffer):
	_x(x), _y(y), _z(z), _xAngle(xAngle), _yAngle(yAngle), _zAngle(zAngle), _tX(tX), _tY(tY), _tZ(tZ),
    _pImmediateContext(pImmediateContext), _t(0.0f), _driverType(driverType), _pVertexShader(pVertexShader), _pPixelShader(pPixelShader), _pConstantBuffer(pConstantBuffer)
{
}

void Cube::Draw(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection)
{
    DirectX::XMMATRIX mWorld =
        DirectX::XMMatrixRotationZ(_zAngle) *
        DirectX::XMMatrixRotationY(_yAngle) *
        DirectX::XMMatrixRotationX(_xAngle) *
        DirectX::XMMatrixTranslation(_x, _y, _z) *
        DirectX::XMMatrixIdentity();

    DirectX::XMMATRIX mView = XMLoadFloat4x4(&view);
    DirectX::XMMATRIX mProjection = XMLoadFloat4x4(&projection);
    //
    // Update variables
    //
    ConstantBuffer cb;
    cb.mWorld = XMMatrixTranspose(mWorld);
    cb.mView = XMMatrixTranspose(mView);
    cb.mProjection = XMMatrixTranspose(mProjection);

    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);

    //
    // Renders a triangle
    //
    _pImmediateContext->VSSetShader(_pVertexShader, nullptr, 0);
    _pImmediateContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
    _pImmediateContext->PSSetConstantBuffers(0, 1, &_pConstantBuffer);
    _pImmediateContext->PSSetShader(_pPixelShader, nullptr, 0);
    _pImmediateContext->DrawIndexed(36, 0, 0);
}



void Cube::Update()
{
    if (_driverType == D3D_DRIVER_TYPE_REFERENCE)
    {
        _t += (float)DirectX::XM_PI * 0.0125f;
    }
    else
    {
        static DWORD dwTimeStart = 0;
        DWORD dwTimeCur = GetTickCount();

        if (dwTimeStart == 0)
            dwTimeStart = dwTimeCur;

        _t = (dwTimeCur - dwTimeStart) / 1000.0f;
    }

    _xAngle = _t * _tX;
    _yAngle = _t * _tY;
    _zAngle = _t * _tZ;
}
