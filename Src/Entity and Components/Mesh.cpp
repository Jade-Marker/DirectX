#include "Mesh.h"

void Mesh::CalculateBounds()
{
	float minX, maxX, minY, maxY, minZ, maxZ;
	minX = std::numeric_limits<float>::infinity();
	minY = std::numeric_limits<float>::infinity();
	minZ = std::numeric_limits<float>::infinity();
	maxX = -std::numeric_limits<float>::infinity();
	maxY = -std::numeric_limits<float>::infinity();
	maxZ = -std::numeric_limits<float>::infinity();

	float* currentVertex = (float*)((UINT)_pVertices + _positionOffset);	//+ position offset, as the position may not be the first element of the vertex
	for (int i = 0; i < _vertexCount; i++)
	{
		float x, y, z;

		x = currentVertex[0];
		y = currentVertex[1];
		z = currentVertex[2];

		maxX = max(x, maxX);
		maxY = max(y, maxY);
		maxZ = max(z, maxZ);

		minX = min(x, minX);
		minY = min(y, minY);
		minZ = min(z, minZ);

		currentVertex = (float*)((UINT)currentVertex + _vertexSize);
	}

	boundingCenter.x = (minX + maxX) / 2.0f;
	boundingCenter.y = (minY + maxY) / 2.0f;
	boundingCenter.z = (minZ + maxZ) / 2.0f;

	boundingSize.x = maxX - minX;
	boundingSize.y = maxY - minY;
	boundingSize.z = maxZ - minZ;
}

void Mesh::LoadVertices(const void* source)
{
	_pVertices = new unsigned char[_vertexCount * _vertexSize];
	memcpy(_pVertices, source, _vertexSize * _vertexCount);
}

void Mesh::LoadIndices(const void* source)
{
	_pIndices = new WORD[_indexCount];
	memcpy(_pIndices, source, sizeof(WORD) * _indexCount);
}

Mesh::Mesh(const void* vertices, int vertexSize, int vertexCount, const WORD* indices, int indexCount, int positionOffset):
	_vertexCount(vertexCount), _vertexSize(vertexSize), _indexCount(indexCount), _positionOffset(positionOffset), Component(false)
{
	LoadVertices(vertices);
	LoadIndices(indices);
	CalculateBounds();
}

Mesh::~Mesh()
{
	delete[] _pIndices;
	delete[] _pVertices;
}

const void* Mesh::GetVertices()
{
	return _pVertices;
}

int Mesh::GetVertexCount()
{
	return _vertexCount;
}

int Mesh::GetVertexSize()
{
	return _vertexSize;
}

const WORD* Mesh::GetIndices()
{
	return _pIndices;
}

int Mesh::GetIndexCount()
{
	return _indexCount;
}

const XMFLOAT3& Mesh::GetBoundingSize()
{
	return boundingSize;
}

const XMFLOAT3& Mesh::GetBoundingCenter()
{
	return boundingCenter;
}
