#include "Mesh.h"

Mesh::Mesh(Vertices* vertices, WORD* indices, int indexCount):
	_vertices(vertices), _indexCount(indexCount)
{
	_indices = new WORD[_indexCount];

	memcpy(_indices, indices, sizeof(WORD) * _indexCount);
}

Mesh::~Mesh()
{
	delete[] _indices;
	if (_vertices->DeleteOnMeshDelete()) delete _vertices;
}

Vertices* Mesh::GetVertices()
{
	return _vertices;
}

int Mesh::GetVertexCount()
{
	return _vertices->GetCount();
}

WORD* Mesh::GetIndices()
{
	return _indices;
}

int Mesh::GetIndexCount()
{
	return _indexCount;
}