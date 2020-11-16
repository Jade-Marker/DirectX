#pragma once
#include <d3d11_1.h>
#include <directxmath.h>
#include <vector>
#include "Structures.h"
#include "Mesh.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "Constants.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "DeviceManager.h"
#include "ConstantBuffer.h"
#include "InputManager.h"

class SceneObject
{
private:
	VertexBuffer _vertexBuffer;
	IndexBuffer _indexBuffer;

	ConstantBuffer* _pLocalConstantBuffer;
	ID3D11RasterizerState* _rasterState;
	ID3D11RasterizerState* _solidRasterState;
	ID3D11RasterizerState* _wireframeRasterState;
	
	std::vector<Texture*> _textures;

	bool _yDirState;
	bool _xDirState;

	Transform _transform;
	XMFLOAT3 _tScale;

	Mesh* _mesh;
	Shader* _shader;

	SceneObject* _parent;

public:
	SceneObject(const Transform& transform, XMFLOAT3 tScale, SceneObject* parent, Mesh* mesh, bool startInWireFrame, Shader* shader,
		ConstantBuffer* pLocalConstantBuffer, std::vector<Texture*> textures);
	~SceneObject();
	void Draw();
	void Update(float deltaTime);
	XMMATRIX GetWorldMatrix();

private:
	void InitRasterState(bool startInWireFrame);
	void UpdateConstantBuffer();

};

