#pragma once
#include <vector>

class Vertices
{
private:
	void* _data;
	int _size;
	int _count;
	int _stride;
	
	bool _deleteOnMeshDelete;

public:
	Vertices(void* data, int size, int count, bool deleteOnMeshDelete = false);
	~Vertices();

	const void* GetData();
	const int GetSize();
	const int GetCount();
	const int GetStride();
	bool DeleteOnMeshDelete();
};