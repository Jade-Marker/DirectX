#include "RasterState.h"

RasterState::RasterState(bool startInWireFrame)
{
    HRESULT hr;
    D3D11_RASTERIZER_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

    desc.FillMode = D3D11_FILL_WIREFRAME;
    desc.CullMode = D3D11_CULL_NONE;
    hr = DeviceManager::GetDevice()->CreateRasterizerState(&desc, &_wireframeRasterState);

    desc.FillMode = D3D11_FILL_SOLID;
    desc.CullMode = D3D11_CULL_BACK;
    hr = DeviceManager::GetDevice()->CreateRasterizerState(&desc, &_backFaceRasterState);

    desc.FillMode = D3D11_FILL_SOLID;
    desc.CullMode = D3D11_CULL_FRONT;
    hr = DeviceManager::GetDevice()->CreateRasterizerState(&desc, &_frontFaceRasterState);

    if (startInWireFrame)
        _rasterState = _wireframeRasterState;
    else
        _rasterState = _backFaceRasterState;
}

RasterState::~RasterState()
{
    _wireframeRasterState->Release();
    _backFaceRasterState->Release();
    _frontFaceRasterState->Release();
}

void RasterState::Update(float deltaTime)
{
    if (InputManager::GetKeyDown(VK_UP))
    {
        if (_rasterState == _wireframeRasterState)
            _rasterState = _backFaceRasterState;
        else
            _rasterState = _wireframeRasterState;
    }
}

void RasterState::SetRasterState()
{
    DeviceManager::GetContext()->RSSetState(_rasterState);
}

void RasterState::BackFaceCullState()
{
    _rasterState = _backFaceRasterState;
    SetRasterState();
}

void RasterState::FrontFaceCullState()
{
    _rasterState = _frontFaceRasterState;
    SetRasterState();
}
