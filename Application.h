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
#include "Camera.h"
#include "OBJLoader.h"

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
	ID3D11DepthStencilView* _pDepthStencilView;
	ID3D11Texture2D*		_pDepthStencilBuffer;
	ID3D11Buffer*           _pLocalConstantBuffer;
	ID3D11Buffer*           _pGlobalConstantBuffer;
	ID3D11BlendState*		_pBlendState;

	Camera					_camera;
	XMFLOAT4X4              _projection;

	XMFLOAT3				_lightDirection;
	XMFLOAT4				_diffuseMaterial;
	XMFLOAT4				_diffuseLight;
	XMFLOAT4				_ambientMaterial;
	XMFLOAT4				_ambientLight;
	XMFLOAT4				_specularMaterial;
	XMFLOAT4				_specularLight;
	float					_specularPower;
	float					_time;

private:
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitDevice();
	void Cleanup();

	UINT _WindowHeight;
	UINT _WindowWidth;

private:
	std::vector<SceneObject*> _sceneObjects;
	Mesh* _pCubeMesh;
	Mesh* _pFishMesh;
	Mesh* _pPyramidMesh;
	Mesh* _pIcosphereMesh;
	Mesh* _pPlaneMesh;

	std::vector<Shader*> _shaders;

	std::vector<Texture*> _crateTextures;
	std::vector<Texture*> _fishTextures;
	std::vector<Texture*> _blankTextures;

	Mesh* GenerateMesh(int width, int height);

public:
	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);
	void InitTextures();
	void InitMeshes();
	void InitConstantBufferVars();
	void InitSceneObjects();

	void Update(float deltaTime);
	void Draw();
};

