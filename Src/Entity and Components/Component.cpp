#include "Component.h"

Component::Component(bool deleteOnEntityDelete): 
	_deleteOnEntityDelete(deleteOnEntityDelete)
{
}

void Component::Initialise(Entity* parent)
{
	_pParent = parent;
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

void Component::OnSelected()
{
}

bool Component::DeleteOnEntityDelete()
{
	return _deleteOnEntityDelete;
}
