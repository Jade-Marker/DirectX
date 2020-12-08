#pragma once
#include "RasterState.h"
class SkyboxRasterState :
	public RasterState
{
private:
	static ID3D11RasterizerState* GetSkyboxState();

public:
	SkyboxRasterState();
	void SkyboxState();
	virtual bool IsWireframe();

	static void DeallocateStates();
};

