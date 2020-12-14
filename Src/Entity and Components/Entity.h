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
	Entity* _pParent;
	std::vector<Component*> _components;
	bool _isSelectable;

public:
	Entity(const Transform& transform, Entity* parent, std::vector<Component*> components, bool isSelectable);
	~Entity();

	void Draw();
	void Update(float deltaTime);
	void OnSelected();

	XMMATRIX GetWorldMatrix();
	void ChangeParent(Entity* parent);
	Entity* GetParent();
	Transform& GetTransform();
	bool IsSelectable();

	template<typename T>
	T* GetComponent();

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