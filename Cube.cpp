#include "Cube.h"

Cube::Cube(XMFLOAT3 position, XMFLOAT3 angle, XMFLOAT3 tScale,
    ID3D11DeviceContext* pImmediateContext, ID3D11VertexShader* pVertexShader, ID3D11PixelShader* pPixelShader, ID3D11Buffer* pConstantBuffer):
	_position(position), _angle(angle), _tScale(tScale),
    _pImmediateContext(pImmediateContext), _t(0.0f), _pVertexShader(pVertexShader), _pPixelShader(pPixelShader), _pConstantBuffer(pConstantBuffer)
{
}

void Cube::Draw(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection)
{
    DirectX::XMMATRIX mWorld =
        DirectX::XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&_angle)) *
        DirectX::XMMatrixTranslationFromVector(XMLoadFloat3(&_position)) *
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
    static DWORD dwTimeStart = 0;
    DWORD dwTimeCur = GetTickCount();

    if (dwTimeStart == 0)
        dwTimeStart = dwTimeCur;

    _t = (dwTimeCur - dwTimeStart) / 1000.0f;

    _angle.x = _t * _tScale.x;
    _angle.y = _t * _tScale.y;
    _angle.z = _t * _tScale.z;
}
