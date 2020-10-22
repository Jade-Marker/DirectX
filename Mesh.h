#pragma once
#include <windows.h>
#include "Structures.h"
#include "Vertices.h"

class Mesh
{
private:
	Vertices* _vertices;
	WORD* _indices;
	int _indexCount;

public:
	Mesh(Vertices* vertices, WORD* indices, int indexCount);
	~Mesh();

	Vertices* GetVertices();
	int GetVertexCount();
	WORD* GetIndices();
	int GetIndexCount();
};

