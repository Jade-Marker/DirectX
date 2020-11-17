#pragma once
#include "Component.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
class RenderingBuffers :
	public Component
{
private:
	VertexBuffer _vertexBuffer;
	IndexBuffer _indexBuffer;

public:
	virtual void Start();
	void BindBuffers();
};

