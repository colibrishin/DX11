#include "pch.h"
#include "EGEntity.hpp"
#include "EGGameObject.hpp"

#include "EGComponetManager.hpp"
#include "EGGameObjectManager.hpp"
#include "EGSceneManager.hpp"

namespace Engine::Abstract
{
	GameObject::GameObject(const std::wstring& name)
		: Entity(name), mState(Abstract::GameObject::Active)
	{
		mComponents.resize(Enums::COMPONENTTYPE::END);
	}

	void GameObject::Initialize()
	{
		for (auto comp : mComponents)
		{
			if (const auto ptr = comp.lock()) ptr->Initialize();
		}
	}

	void GameObject::AddComponent(const std::weak_ptr<Component>& component)
	{
		const int myOrder = component.lock()->GetUpdateOrder();
		mComponents[myOrder] = component;
	}

	void GameObject::Update()
	{
		for (auto comp : mComponents)
		{
			if (const auto ptr = comp.lock()) ptr->Update();
		}
	}

	void GameObject::FixedUpdate()
	{
		for (auto comp : mComponents)
		{
			if (const auto ptr = comp.lock()) ptr->FixedUpdate();
		}
	}

	void GameObject::Render()
	{
		for (auto comp : mComponents)
		{
			if (const auto ptr = comp.lock()) ptr->Render();
		}
	}
	void GameObject::Destroy()
	{
		for(const auto& comp : mComponents)
		{
			if(const auto component = comp.lock())
			{
				Manager::ComponentManager::Remove(component->GetID());
			}
		}

		Manager::SceneManager::GetActiveScene().lock()->RemoveGameObject(
			std::dynamic_pointer_cast<GameObject>(shared_from_this()), Enums::NONE);
		Manager::GameObjectManager::Remove(GetName());
	}

	GameObject::eState GameObject::GetState() const
	{
		return mState;
	}
}
