#include "LightComponent.h"

void LightComponent::UpdateLightPosition()
{
	if (_isPointLight)
	{
		Vector4D lightPos = _pParent->GetWorldMatrix() * Vector4D(_pParent->GetTransform().Position, 1.0f);

		Light light = LightManager::GetLight(_lightIndex);
		light.SetPosition(lightPos);
		LightManager::SetLight(light, _lightIndex);
	}
}

LightComponent::LightComponent(Light& light)
{
	_lightIndex = LightManager::AddLight(light);
}

void LightComponent::Start()
{
	_isPointLight = (LightManager::GetLight(_lightIndex).GetPosition().w == 1.0f);	//If w = 1, the light is a point light and if w = 0 it is a directional light

	UpdateLightPosition();	
}

void LightComponent::Update(float deltaTime)
{
	UpdateLightPosition();
}