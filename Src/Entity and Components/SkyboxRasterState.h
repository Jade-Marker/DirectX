#pragma once
#include "RasterState.h"
class SkyboxRasterState :
	public RasterState
{
private:
	ID3D11RasterizerState* _skyboxRasterState;

public:
	SkyboxRasterState();
	~SkyboxRasterState();
	void SkyboxState();
	virtual bool IsWireframe();
};

