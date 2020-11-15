#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <vector>
#include "Structures.h"
#include "resource.h"
#include "SceneObject.h"
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

	UINT _WindowHeight;
	UINT _WindowWidth;


	ConstantBuffer			_localConstantBuffer;
	ConstantBuffer			_globalConstantBuffer;

	XMFLOAT4				_diffuseMaterial;
	XMFLOAT4				_ambientMaterial;
	XMFLOAT4				_specularMaterial;
	float					_time;

	Camera* _pCamera;

	std::vector<SceneObject*> _sceneObjects;
	Mesh* _pFishMesh;
	Mesh* _pPlaneMesh;

	std::vector<Shader*> _shaders;

	std::vector<Texture*> _crateTextures;
	std::vector<Texture*> _fishTextures;
	std::vector<Texture*> _blankTextures;

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

	Mesh* GenerateMesh(int width, int height);
	void InitTextures();
	void InitMeshes();
	void InitConstantBufferVars();
	void InitSceneObjects();
	void InitLights();
	void ResizeRenderTargetView();
};