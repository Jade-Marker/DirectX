#include "SkyboxRasterState.h"

ID3D11RasterizerState* SkyboxRasterState::GetSkyboxState()
{
	ID3D11RasterizerState* skyboxRaster = nullptr;

	if (skyboxRaster == nullptr)
		CreateRasterState(D3D11_FILL_SOLID, D3D11_CULL_NONE, skyboxRaster);

	return skyboxRaster;
}

SkyboxRasterState::SkyboxRasterState() :
	RasterState(false)
{
	
}

void SkyboxRasterState::SkyboxState()
{
	SetRasterState(GetSkyboxState());
}

bool SkyboxRasterState::IsWireframe()
{
	//The skybox should never be wireframe, so return false
	return false;
}

void SkyboxRasterState::DeallocateStates()
{
	GetSkyboxState()->Release();

	RasterState::DeallocateStates();
}
