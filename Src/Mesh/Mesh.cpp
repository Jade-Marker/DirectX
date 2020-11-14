#include "Mesh.h"

Mesh::Mesh(const void* vertices, int vertexSize, int vertexCount, const WORD* indices, int indexCount):
	_vertexCount(vertexCount), _vertexSize(vertexSize), _indexCount(indexCount)
{
	_vertices = new unsigned char[_vertexCount * _vertexSize];
	memcpy(_vertices, vertices, vertexSize * vertexCount);

	_indices = new WORD[_indexCount];
	memcpy(_indices, indices, sizeof(WORD) * _indexCount);
}

Mesh::~Mesh()
{
	delete[] _indices;
	delete[] _vertices;
}

const void* Mesh::GetVertices()
{
	return _vertices;
}

int Mesh::GetVertexCount()
{
	return _vertexCount;
}

int Mesh::GetVertexSize()
{
	return _vertexSize;
}

int Mesh::GetVerticesSize()
{
	return _vertexSize * _vertexCount;
}

WORD* Mesh::GetIndices()
{
	return _indices;
}

int Mesh::GetIndexCount()
{
	return _indexCount;
}