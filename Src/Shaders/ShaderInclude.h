#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include <fstream>
#include "Constants.h"

class ShaderInclude : public ID3DInclude
{
public:
	HRESULT __stdcall Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes);
	HRESULT __stdcall Close(LPCVOID pData);
};

