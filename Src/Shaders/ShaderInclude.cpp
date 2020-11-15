#include "ShaderInclude.h"

HRESULT ShaderInclude::Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes)
{
	std::string filePath;
	std::ifstream file;
	char* buffer;
	UINT bufferSize;


	switch (IncludeType)
	{
	case D3D_INCLUDE_LOCAL:
	case D3D_INCLUDE_SYSTEM:
		filePath = cShadersPath + "\\" + pFileName;
		break;
	default:
		return E_FAIL;
	}


	file = std::ifstream(filePath.c_str(), std::ios::binary | std::ios::ate);
	if (!file.good())
		return E_FAIL;


	file.seekg(0, std::ios::end);
	bufferSize = file.tellg();

	buffer = new char [bufferSize];

	file.seekg(0, std::ios::beg);
	file.read(buffer, bufferSize);
	file.close();

	*ppData = buffer;
	*pBytes = bufferSize;

	return S_OK;
}

HRESULT ShaderInclude::Close(LPCVOID pData)
{
	char* buffer = (char*)pData;

	delete[] buffer;

	return S_OK;
}
