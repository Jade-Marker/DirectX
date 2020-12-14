#pragma once
#include "Component.h"
#include "Light.h"
#include "LightManager.h"
class LightComponent :
	public Component
{
private:
	int _lightIndex;
	bool _isPointLight;

private:
	void UpdateLightPosition();

public:
	LightComponent(Light& light);

	virtual void Start();
	virtual void Update(float deltaTime);
};

