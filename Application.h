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
#include "Vertices.h"

using namespace DirectX;

class Application
{
private:
	HINSTANCE               _hInst;
	HWND                    _hWnd;
	D3D_DRIVER_TYPE         _driverType;
	D3D_FEATURE_LEVEL       _featureLevel;
	ID3D11Device*           _pd3dDevice;
	ID3D11DeviceContext*    _pImmediateContext;
	IDXGISwapChain*         _pSwapChain;
	ID3D11RenderTargetView* _pRenderTargetView;
	ID3D11DepthStencilView* _depthStencilView;
	ID3D11Texture2D*		_depthStencilBuffer;
	ID3D11Buffer*           _pLocalConstantBuffer;
	ID3D11Buffer*           _pGlobalConstantBuffer;
	ID3D11BlendState*		_pBlendState;

	XMFLOAT4X4              _world;
	XMFLOAT4X4              _view;
	XMFLOAT4X4              _projection;

	XMFLOAT3				_lightDirection;
	XMFLOAT4				_diffuseMaterial;
	XMFLOAT4				_diffuseLight;
	XMFLOAT4				_ambientMaterial;
	XMFLOAT4				_ambientLight;
	XMFLOAT4				_specularMaterial;
	XMFLOAT4				_specularLight;
	float					_specularPower;
	XMFLOAT3				_cameraPos;
	float					_time;

private:
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitDevice();
	void Cleanup();

	UINT _WindowHeight;
	UINT _WindowWidth;

private:
	std::vector<SceneObject*> _sceneObjects;
	Mesh* _cubeMesh;
	Mesh* _pyramidMesh;
	Mesh* _icosphereMesh;
	Mesh* _planeMesh;

	Shader* _dx11Shader;
	Shader* _basicShader;
	Shader* _discardShader;
	Shader* _waterShader;

	Mesh* GenerateMesh(int width, int height);

public:
	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	void Update(float deltaTime);
	void Draw();
};

