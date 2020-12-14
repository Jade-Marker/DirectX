#include "LightComponent.h"

void LightComponent::UpdateLightPosition()
{
	if (_isPointLight)
	{
		XMMATRIX worldMatrix = _parent->GetWorldMatrix();

		XMFLOAT3 transformPosition = _parent->GetTransform().Position;
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
	_isPointLight = (LightManager::GetLight(_lightIndex).GetPosition().w == 1.0f);

	UpdateLightPosition();	
}

void LightComponent::Update(float deltaTime)
{
	UpdateLightPosition();
}