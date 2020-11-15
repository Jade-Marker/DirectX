#pragma once
#include <windows.h>
#include "Structures.h"

class Mesh
{
private:
	void* _vertices;
	int _vertexCount;
	int _vertexSize;

	WORD* _indices;
	int _indexCount;

public:
	Mesh(const void* vertices, int vertexSize, int vertexCount, const WORD* indices, int indexCount);
	~Mesh();

	const void* GetVertices();
	int GetVertexCount();
	int GetVertexSize();
	const WORD* GetIndices();
	int GetIndexCount();
};

