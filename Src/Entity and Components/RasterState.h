#pragma once
#include <d3d11.h>
#include "Component.h"
#include "DeviceManager.h"
#include "InputManager.h"
class RasterState :
	public Component
{
private:
	ID3D11RasterizerState* _rasterState;
	ID3D11RasterizerState* _solidRasterState;
	ID3D11RasterizerState* _wireframeRasterState;

public:
	RasterState(bool startInWireFrame);
	virtual void Update(float deltaTime);
	void SetRasterState();
};

