#pragma once
#include "Buffer.h"
#include "Mesh.h"

class IndexBuffer:Buffer
{
public:
	IndexBuffer();

	HRESULT Initialise(Mesh* mesh);
	virtual void Bind(Shader* shader = nullptr, UINT slot = 0);
};

