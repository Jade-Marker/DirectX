#include "EntityManager.h"

EntityManager* EntityManager::GetInstance()
{
	static EntityManager instance;

	return &instance;
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

void EntityManager::ClearEntities()
{
	EntityManager* instance = GetInstance();

	for (int i = 0; i < instance->_entities.size(); i++)
		delete instance->_entities[i];

	instance->_entities.clear();
}
