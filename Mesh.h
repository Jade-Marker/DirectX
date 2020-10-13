#pragma once
#include <windows.h>
#include "Structures.h"

class Mesh
{
private:
	SimpleVertex* _vertices;
	int _vertexCount;
	WORD* _indices;
	int _indexCount;

public:
	Mesh(SimpleVertex* vertices, int vertexCount, WORD* indices, int indexCount);
	~Mesh();

	SimpleVertex* GetVertices();
	int GetVertexCount();
	WORD* GetIndices();
	int GetIndexCount();
};

