#include "RasterState.h"

void RasterState::SetRasterState(ID3D11RasterizerState* state)
{
    _rasterState = state;
    DeviceManager::GetContext()->RSSetState(_rasterState);
}

void RasterState::CreateRasterState(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode, ID3D11RasterizerState*& rasterState)
{
    HRESULT hr;
    D3D11_RASTERIZER_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
    desc.FillMode = fillMode;
    desc.CullMode = cullMode;
    hr = DeviceManager::GetDevice()->CreateRasterizerState(&desc, &rasterState);
}

ID3D11RasterizerState* RasterState::GetBackFaceState()
{
    static ID3D11RasterizerState* backfaceState = nullptr;

    if (backfaceState == nullptr)
        CreateRasterState(D3D11_FILL_SOLID, D3D11_CULL_BACK, backfaceState);

    return backfaceState;
}

ID3D11RasterizerState* RasterState::GetFrontFaceState()
{
    static ID3D11RasterizerState* frontfaceState = nullptr;

    if (frontfaceState == nullptr)
        CreateRasterState(D3D11_FILL_SOLID, D3D11_CULL_FRONT, frontfaceState);

    return frontfaceState;
}

ID3D11RasterizerState* RasterState::GetWireframeState()
{
    static ID3D11RasterizerState* wireframeState = nullptr;

    if (wireframeState == nullptr)
        CreateRasterState(D3D11_FILL_WIREFRAME, D3D11_CULL_NONE, wireframeState);

    return wireframeState;
}

RasterState::RasterState(bool startInWireFrame):
    _wireframeMode(startInWireFrame), _rasterState(nullptr)
{
}

void RasterState::Update(float deltaTime)
{
    if (InputManager::GetKeyDown(VK_UP))
    {
        _wireframeMode = !_wireframeMode;
    }
}

void RasterState::BackFaceCullState()
{
    SetRasterState(GetBackFaceState());
}

void RasterState::FrontFaceCullState()
{
    SetRasterState(GetFrontFaceState());
}

void RasterState::WireframeState()
{
    SetRasterState(GetWireframeState());
}

bool RasterState::IsWireframe()
{
    return _wireframeMode;
}

void RasterState::DeallocateStates()
{
    GetWireframeState()->Release();
    GetBackFaceState()->Release();
    GetFrontFaceState()->Release();
}
