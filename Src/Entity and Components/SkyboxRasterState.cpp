#include "SkyboxRasterState.h"

SkyboxRasterState::SkyboxRasterState() :
	RasterState(false), _skyboxRasterState(nullptr)
{
	HRESULT hr;
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_NONE;
	hr = DeviceManager::GetDevice()->CreateRasterizerState(&desc, &_skyboxRasterState);
}

SkyboxRasterState::~SkyboxRasterState()
{
	_skyboxRasterState->Release();
}

void SkyboxRasterState::SkyboxState()
{
	_rasterState = _skyboxRasterState;
	SetRasterState();
}

bool SkyboxRasterState::IsWireframe()
{
	return false;
}
