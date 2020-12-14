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
	static void BindLightBuffer(Shader* shader, int slot);
	static int AddLight(Light light);
	static int GetNumLights();
	static void UpdateLights();
	static Light GetLight(int index);
	static void SetLight(const Light& light, int index);
};

