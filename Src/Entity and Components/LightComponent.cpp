#include "LightComponent.h"

void LightComponent::UpdateLightPosition()
{
	if (_isPointLight)
	{
		XMMATRIX worldMatrix = _pParent->GetWorldMatrix();

		XMFLOAT3 transformPosition = _pParent->GetTransform().Position;
		XMFLOAT4 lightPos = XMFLOAT4(transformPosition.x, transformPosition.y, transformPosition.z, 1.0f);

		XMStoreFloat4(&lightPos, XMVector3Transform(XMLoadFloat4(&lightPos), worldMatrix));

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