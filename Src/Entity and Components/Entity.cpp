#include "Entity.h"
#include "Component.h"
#include "CameraManager.h"

Entity::Entity(const Transform& transform, Entity* parent, std::vector<Component*> components) :
	_transform(transform), _parent(parent), _components(components)
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

bool Entity::CompareDistance(Entity* object, Entity* other)
{
    XMVECTOR objectPos;
    XMVECTOR otherPos;
    XMVECTOR blank;
    XMMatrixDecompose(&blank, &blank, &objectPos, object->GetWorldMatrix());
    XMMatrixDecompose(&blank, &blank, &otherPos, other->GetWorldMatrix());

    XMVECTOR cameraPos = XMLoadFloat3(&CameraManager::GetMainCamera()->GetPosition());

    return (XMVector3LengthSq(cameraPos - objectPos).m128_f32[0] < XMVector3LengthSq(cameraPos - otherPos).m128_f32[0]);
}
