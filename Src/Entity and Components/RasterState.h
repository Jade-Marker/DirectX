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
	bool _wireframeMode;

protected:
	void SetRasterState(ID3D11RasterizerState* state);
	static void CreateRasterState(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode, ID3D11RasterizerState*& rasterState);
	static ID3D11RasterizerState* GetBackFaceState();
	static ID3D11RasterizerState* GetFrontFaceState();
	static ID3D11RasterizerState* GetWireframeState();

public:
	RasterState(bool startInWireFrame);
	virtual void Update(float deltaTime);
	void BackFaceCullState();
	void FrontFaceCullState();
	void WireframeState();
	virtual bool IsWireframe();

	static void DeallocateStates();
};

