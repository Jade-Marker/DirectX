#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <directxmath.h>
#include <fstream>		//For loading in an external file
#include <vector>		//For storing the XMFLOAT3/2 variables
#include <map>			//For fast searching when re-creating the index buffer
#include "Structures.h"
#include "Mesh.h"

using namespace DirectX;

//Note, this code is an altered version of code we were given in a tutorial
//I had to alter it as the way it set up its mesh struct wasn't compatible with my Mesh class

namespace OBJLoader
{
	//The only method you'll need to call
	Mesh* Load(char* filename, bool invertTexCoords = true);

	//Helper methods for the above method
	//Searhes to see if a similar vertex already exists in the buffer -- if true, we re-use that index
	bool FindSimilarVertex(const LightVertex& vertex, std::map<LightVertex, unsigned short>& vertToIndexMap, unsigned short& index);

	//Re-creates a single index buffer from the 3 given in the OBJ file
	void CreateIndices(const std::vector<XMFLOAT3>& inVertices, const std::vector<XMFLOAT2>& inTexCoords, const std::vector<XMFLOAT3>& inNormals, std::vector<unsigned short>& outIndices, std::vector<XMFLOAT3>& outVertices, std::vector<XMFLOAT2>& outTexCoords, std::vector<XMFLOAT3>& outNormals);
};