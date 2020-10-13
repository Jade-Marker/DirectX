#include "Mesh.h"

Mesh::Mesh(SimpleVertex* vertices, int vertexCount, WORD* indices, int indexCount):
	_vertexCount(vertexCount), _indexCount(indexCount)
{
	_vertices = new SimpleVertex[_vertexCount];
	_indices = new WORD[_indexCount];

	memcpy(_vertices, vertices, sizeof(SimpleVertex) * _vertexCount);
	memcpy(_indices, indices, sizeof(WORD) * _indexCount);
}

Mesh::~Mesh()
{
	delete[] _vertices;
	delete[] _indices;
}

SimpleVertex* Mesh::GetVertices()
{
	return _vertices;
}

int Mesh::GetVertexCount()
{
	return _vertexCount;
}

WORD* Mesh::GetIndices()
{
	return _indices;
}

int Mesh::GetIndexCount()
{
	return _indexCount;
}
