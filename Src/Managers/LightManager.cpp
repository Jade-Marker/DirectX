#include "LightManager.h"

LightManager::LightManager()
{
	_pLightBuffer = new StructuredBuffer(nullptr, cInitMaxNumLights, sizeof(Light));
}

LightManager::~LightManager()
{
	delete _pLightBuffer;
}

LightManager* LightManager::GetInstance()
{
	static LightManager instance;

	return &instance;
}

void LightManager::BindLightBuffer(Shader* shader, int slot)
{
	LightManager* instance = GetInstance();

	instance->_pLightBuffer->Bind(shader, slot);
}

int LightManager::AddLight(Light light)
{
	LightManager* instance = GetInstance();
	
	instance->_pLightBuffer->UpdateBuffer(&light, sizeof(Light), sizeof(Light) * (instance->_lights.size()));
	instance->_lights.push_back(light);

	//Return the index of the light, so that the light can be referenced elsewhere
	return instance->_lights.size() - 1;
}

int LightManager::GetNumLights()
{
	LightManager* instance = GetInstance();

	return instance->_lights.size();
}

void LightManager::UpdateLights()
{
	LightManager* instance = GetInstance();

	instance->_pLightBuffer->UpdateBuffer(instance->_lights.data(), sizeof(Light) * instance->_lights.size(), 0);
}

Light LightManager::GetLight(int index)
{
	LightManager* instance = GetInstance();
	
	return instance->_lights[index];
}

void LightManager::SetLight(const Light& light, int index)
{
	LightManager* instance = GetInstance();

	instance->_lights[index] = light;
}
