#pragma once
#include <vector>
#include "Light.h" 
#include "Shader.h"
#include "StructuredBuffer.h"

class LightManager
{
private:
	StructuredBuffer* _pLightBuffer;
	std::vector<Light> _lights;

private:
	LightManager();
	~LightManager();
	static LightManager* GetInstance();

public:
	static void Bind(Shader* shader, int slot);
	static Light* AddLight(Light light);
	static int GetNumLights();
	static void UpdateLights();
};

