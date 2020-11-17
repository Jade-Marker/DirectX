#pragma once
#include "Entity.h"

class Component
{
protected:
	Entity* _parent;

public:
	Component();

	void Initialise(Entity* parent);
	virtual void Start();
	virtual void Draw();
	virtual void Update(float deltaTime);
};

