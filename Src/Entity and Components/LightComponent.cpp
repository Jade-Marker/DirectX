#include "LightComponent.h"

void LightComponent::UpdateLightPosition()
{
	if (_isPointLight)
	{
		XMMATRIX worldMatrix = _parent->GetWorldMatrix();

		XMFLOAT3 transformPosition = _parent->GetTransform().Position;
		XMFLOAT4 lightPos = XMFLOAT4(transformPosition.x, transformPosition.y, transformPosition.z, 1.0f);

		XMStoreFloat4(&lightPos, XMVector3Transform(XMLoadFloat4(&lightPos), worldMatrix));

		_pLightData->SetPosition(lightPos);
	}
}

LightComponent::LightComponent(Light& light)
{
	_pLightData = LightManager::AddLight(light);
}

void LightComponent::Start()
{
	_isPointLight = (_pLightData->GetPosition().w == 1.0f);

	UpdateLightPosition();	
}

void LightComponent::Update(float deltaTime)
{
	UpdateLightPosition();
}