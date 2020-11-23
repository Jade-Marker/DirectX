#include "RasterState.h"

RasterState::RasterState(bool startInWireFrame):
    _wireframeMode(startInWireFrame)
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
        _wireframeMode = !_wireframeMode;
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

void RasterState::WireframeState()
{
    _rasterState = _wireframeRasterState;
    SetRasterState();
}

bool RasterState::IsWireframe()
{
    return _wireframeMode;
}
