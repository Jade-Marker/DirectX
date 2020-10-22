#include "Vertices.h"

Vertices::Vertices(void* data, int size, int count, bool deleteOnMeshDelete):
	_data(nullptr), _size(size), _count(count), _stride(size/count), _deleteOnMeshDelete(deleteOnMeshDelete)
{
	_data = new unsigned char[size];
	memcpy(_data, data, size);
}

Vertices::~Vertices()
{
	delete[] _data;
}

const void* Vertices::GetData()
{
	return _data;
}

const int Vertices::GetSize()
{
	return _size;
}

const int Vertices::GetCount()
{
	return _count;
}

const int Vertices::GetStride()
{
	return _stride;
}

bool Vertices::DeleteOnMeshDelete()
{
	return _deleteOnMeshDelete;
}
