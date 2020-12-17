#pragma once
#include <windows.h>
#include "Component.h"

class Mesh : public Component
{
private:
	//Vertices stored as a void* instead of an array or vector so that any type of vertex can be used. array/vector doesn't work with polymorphism unless each element is a pointer
	//In this case however, we want to store the vertices as a continuous block of memory, so arrays/vectors just won't work for multiple vertex types
	void* _pVertices;	
	int _vertexCount;
	int _vertexSize;

	WORD* _pIndices;
	int _indexCount;

	int _positionOffset;

	XMFLOAT3 _boundingSize;
	XMFLOAT3 _boundingCenter;

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

