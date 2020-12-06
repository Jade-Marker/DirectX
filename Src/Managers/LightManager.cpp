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

void LightManager::Bind(Shader* shader, int slot)
{
	LightManager* instance = GetInstance();

	instance->_pLightBuffer->Bind(shader, slot);
}

Light* LightManager::AddLight(Light light)
{
	LightManager* instance = GetInstance();
	
	instance->_pLightBuffer->Update(&light, sizeof(Light), sizeof(Light) * (instance->_lights.size()));
	instance->_lights.push_back(light);

	return &instance->_lights[instance->_lights.size() - 1];
}

int LightManager::GetNumLights()
{
	LightManager* instance = GetInstance();

	return instance->_lights.size();
}

void LightManager::UpdateLights()
{
	LightManager* instance = GetInstance();

	instance->_pLightBuffer->Update(instance->_lights.data(), sizeof(Light) * instance->_lights.size(), 0);
}
