#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "Structures.h"
#include "Mesh.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "Constants.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "DeviceManager.h"

class SceneObject
{
private:
	VertexBuffer _vertexBuffer;
	IndexBuffer _indexBuffer;

	ID3D11Buffer* _pLocalConstantBuffer;
	ID3D11RasterizerState* _rasterState;
	ID3D11RasterizerState* _solidRasterState;
	ID3D11RasterizerState* _wireframeRasterState;
	
	std::vector<Texture*> _textures;

	bool _rasterKeyDown;
	bool _yDirState;
	bool _xDirState;

	XMFLOAT3 _position;
	XMFLOAT3 _angle;
	XMFLOAT3 _scale;
	XMFLOAT3 _tScale;

	Mesh* _mesh;
	Shader* _shader;

	SceneObject* _parent;

public:
	SceneObject(XMFLOAT3 position, XMFLOAT3 angle, XMFLOAT3 scale, XMFLOAT3 tScale, SceneObject* parent, Mesh* mesh, bool startInWireFrame, Shader* shader,
		ID3D11Buffer* pLocalConstantBuffer, std::vector<Texture*> textures);
	~SceneObject();
	void Draw();
	void Update(float deltaTime);
	XMMATRIX GetWorldMatrix();

private:
	void InitRasterState(bool startInWireFrame);
	void UpdateConstantBuffer();

};

