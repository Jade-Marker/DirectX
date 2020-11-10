#pragma once
#include "Buffer.h"
#include "Mesh.h"


class VertexBuffer: Buffer
{
private:
	Mesh* _pMesh;

public:
	VertexBuffer();

	HRESULT Initialise(Mesh* mesh);
	virtual void Bind(Shader* shader = nullptr, UINT slot = 0);
};

