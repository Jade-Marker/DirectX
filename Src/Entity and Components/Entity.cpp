#include "Entity.h"
#include "Component.h"
#include "CameraManager.h"

Entity::Entity(const Transform& transform, Entity* parent, std::vector<Component*> components, bool isSelectable) :
	_transform(transform), _pParent(parent), _components(components), _isSelectable(isSelectable)
{
    for (int i = 0; i < _components.size(); i++)
        _components[i]->Initialise(this);

    for (int i = 0; i < _components.size(); i++)
        _components[i]->Start();
}

Entity::~Entity()
{
    for (int i = 0; i < _components.size(); i++)
        if (_components[i]->DeleteOnEntityDelete()) delete _components[i];
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

void Entity::OnSelected()
{
    for (int i = 0; i < _components.size(); i++)
        _components[i]->OnSelected();
}

Matrix Entity::GetWorldMatrix()
{
    Matrix world = _transform.GetWorldMatrix();

    if (_pParent != nullptr)
    {
        world = _pParent->GetWorldMatrix() * world;
    }

    return world;
}

void Entity::ChangeParent(Entity* parent)
{
    _pParent = parent;
}

Entity* Entity::GetParent()
{
	return _pParent;
}

Transform& Entity::GetTransform()
{
    return _transform;
}

bool Entity::IsSelectable()
{
	return _isSelectable;
}

bool Entity::CompareDistance(Entity* object, Entity* other)
{
    Vector3D objectPos = object->GetWorldMatrix() * Vector3D();
    Vector3D otherPos = other->GetWorldMatrix() * Vector3D();
    Vector3D cameraPos = CameraManager::GetMainCamera()->GetPosition();

    return ((cameraPos - objectPos).Square() > (cameraPos - otherPos).Square());
}