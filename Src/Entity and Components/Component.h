#pragma once
#include "Entity.h"

class Component
{
protected:
	Entity* _parent;
	bool _deleteOnEntityDelete;

public:
	Component(bool deleteOnEntityDelete = true);

	void Initialise(Entity* parent);
	virtual void Start();
	virtual void Draw();
	virtual void Update(float deltaTime);
	virtual void OnSelected();

	bool DeleteOnEntityDelete();
};

