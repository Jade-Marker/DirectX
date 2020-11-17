#include "RenderingBuffers.h"

void RenderingBuffers::Start()
{
	Mesh* pMesh = _parent->GetComponent<Mesh>();

	_vertexBuffer.Initialise(pMesh);
	_indexBuffer.Initialise(pMesh);
}


void RenderingBuffers::BindBuffers()
{
	_vertexBuffer.Bind();
	_indexBuffer.Bind();
}