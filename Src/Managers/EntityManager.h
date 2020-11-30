#pragma once

#include "Entity.h"

class EntityManager
{
private:
	std::vector<Entity*> _entities;
	static EntityManager* GetInstance();

public:
	static void AddEntity(Entity* entity);
	static const std::vector<Entity*>& GetEntities();
	static void ClearEntities();
};

