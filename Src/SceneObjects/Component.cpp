#include "Component.h"

Component::Component()
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
