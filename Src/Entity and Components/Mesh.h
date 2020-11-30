#pragma once
#include <windows.h>
#include "Component.h"

class Mesh : public Component
{
private:
	void* _vertices;
	int _vertexCount;
	int _vertexSize;

	WORD* _indices;
	int _indexCount;

	int _positionOffset;

	XMFLOAT3 boundingSize;
	XMFLOAT3 boundingCenter;

private:
	void CalculateBounds();
	void LoadVertices(const void* source);
	void LoadIndices(const void* source);

public:
	Mesh(const void* vertices, int vertexSize, int vertexCount, const WORD* indices, int indexCount, int positionOffset = 0);
	~Mesh();

	const void* GetVertices();
	int GetVertexCount();
	int GetVertexSize();
	const WORD* GetIndices();
	int GetIndexCount();

	const XMFLOAT3& GetBoundingSize();
	const XMFLOAT3& GetBoundingCenter();
};

