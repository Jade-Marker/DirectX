#include "Entity.h"
#include "Component.h"

Entity::Entity(const Transform& transform, Entity* parent, std::vector<Component*> components) :
	_transform(transform), _parent(parent), _components(components)
{
    for (int i = 0; i < _components.size(); i++)
        _components[i]->Initialise(this);

    for (int i = 0; i < _components.size(); i++)
        _components[i]->Start();
}

void Entity::Draw()
{
    for (int i = 0; i < _components.size(); i++)
        _components[i]->Draw();
}

void Entity::Update(float deltaTime)
{
    for (int i = 0; i < _components.size(); i++)
        _components[i]->Update(deltaTime);
}

XMMATRIX Entity::GetWorldMatrix()
{
    DirectX::XMMATRIX world = _transform.GetWorldMatrix();

    if (_parent != nullptr)
    {
        world = world * _parent->GetWorldMatrix();
    }

    return world;
}

Transform& Entity::GetTransform()
{
    return _transform;
}