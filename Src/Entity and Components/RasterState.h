#pragma once
#include <d3d11.h>
#include "Component.h"
#include "DeviceManager.h"
#include "InputManager.h"
class RasterState :
	public Component
{
protected:
	ID3D11RasterizerState* _rasterState;
	ID3D11RasterizerState* _backFaceRasterState;
	ID3D11RasterizerState* _frontFaceRasterState;
	ID3D11RasterizerState* _wireframeRasterState;
	bool _wireframeMode;

public:
	RasterState(bool startInWireFrame);
	~RasterState();
	virtual void Update(float deltaTime);
	void SetRasterState();
	void BackFaceCullState();
	void FrontFaceCullState();
	void WireframeState();
	virtual bool IsWireframe();
};

