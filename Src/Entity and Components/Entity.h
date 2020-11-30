#pragma once
#include <d3d11_1.h>
#include <directxmath.h>
#include <vector>
#include "Structures.h"

class Component;

class Entity
{
private:
	Transform _transform;
	Entity* _parent;
	std::vector<Component*> _components;

public:
	Entity(const Transform& transform, Entity* parent, std::vector<Component*> components);
	~Entity();
	void Draw();
	void Update(float deltaTime);
	void OnSelected();
	XMMATRIX GetWorldMatrix();

	template<typename T>
	T* GetComponent();

	Transform& GetTransform();

	static bool CompareDistance(Entity* object, Entity* other);
};

template<typename T>
T* Entity::GetComponent()
{
	T* component = nullptr;

	for (int i = 0; i < _components.size(); i++)
	{
		component = dynamic_cast<T*>(_components[i]);

		if (component != nullptr)
			break;
	}

	return component;
}