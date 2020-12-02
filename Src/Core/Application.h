#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <vector>
#include <algorithm>
#include "Structures.h"
#include "resource.h"
#include "Entity.h"
#include "Mesh.h"
#include "Shader.h"
#include "Constants.h"
#include "Camera.h"
#include "OBJLoader.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "StructuredBuffer.h"
#include "DeviceManager.h"
#include "ConstantBuffer.h"
#include "InputManager.h"
#include "Meshes.h"
#include "Material.h"
#include "Renderer.h"
#include "RasterState.h"
#include "Rotator.h"
#include "RenderingBuffers.h"
#include "CameraManager.h"
#include "DebugLogManager.h"
#include "CameraController.h"
#include "EntityManager.h"
#include "SelectionHide.h"

using namespace DirectX;

class Application
{
private:
	HINSTANCE               _hInst;
	HWND                    _hWnd;
	D3D_DRIVER_TYPE         _driverType;
	D3D_FEATURE_LEVEL       _featureLevel;
	IDXGISwapChain*         _pSwapChain;
	ID3D11RenderTargetView* _pRenderTargetView;
	ID3D11DepthStencilView* _pDepthStencilView;
	ID3D11Texture2D*		_pDepthStencilBuffer;
	ID3D11BlendState*		_pBlendState;

	float _clearColor[4];

	UINT _WindowHeight;
	UINT _WindowWidth;


	ConstantBuffer			_localConstantBuffer;
	ConstantBuffer			_globalConstantBuffer;

	float					_time;

	Mesh* _pFishMesh;
	Mesh* _pPlaneMesh;

	std::vector<Shader*> _shaders;
	Shader* _dx11Shader;
	Shader* _discardShader;
	Shader* _basicShader;
	Shader* _waterShader;

	Texture* _crateColour;
	Texture* _crateSpecular;
	Texture* _fishColour;
	Texture* _fishAmbient;

	StructuredBuffer* _pLightBuffer;
	std::vector<Light>		_lights;

public:
	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	void Update(float deltaTime);
	void Draw();
	void Resize(UINT width, UINT height);

private:
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitDevice();
	void InitViewport();
	void InitDepthStencilBuffer();
	void Cleanup();

	void InitTextures();
	void InitMeshes();
	void InitShaders();
	void InitConstantBufferVars();
	void InitEntities();
	void InitLights();
	void ResizeRenderTargetView();
};