#include "Component.h"

Component::Component(bool deleteOnEntityDelete): 
	_deleteOnEntityDelete(deleteOnEntityDelete)
{
}

void Component::Initialise(Entity* parent)
{
	_parent = parent;
}

void Component::Start()
{
}

void Component::Draw()
{
}

void Component::Update(float deltaTime)
{
}

bool Component::DeleteOnEntityDelete()
{
	return _deleteOnEntityDelete;
}
