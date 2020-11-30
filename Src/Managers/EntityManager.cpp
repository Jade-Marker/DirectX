#include "EntityManager.h"

EntityManager* EntityManager::GetInstance()
{
	static EntityManager instance;

	return &instance;
}

EntityManager::~EntityManager()
{
	for (int i = 0; i < _entities.size(); i++)
		delete _entities[i];
}

void EntityManager::AddEntity(Entity* entity)
{
	EntityManager* instance = GetInstance();

	instance->_entities.push_back(entity);
}

const std::vector<Entity*>& EntityManager::GetEntities()
{
	EntityManager* instance = GetInstance();

	return instance->_entities;
}
