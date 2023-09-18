#pragma once
#include "EGComponent.hpp"
#include "EGEntity.hpp"

namespace Engine::Abstract
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject(const std::wstring& name);
		~GameObject() override = default;

		void AddComponent(const std::weak_ptr<Component>& component);
		template <typename T>
		std::weak_ptr<T> GetComponent()
		{
			for (auto c : mComponents)
			{
				if (const auto component = std::dynamic_pointer_cast<T>(c.lock()))
				{
					return component;
				}
			}

			return {};
		}

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		eState mState;
		std::vector<std::weak_ptr<Component>> mComponents{};
	};

	inline GameObject::GameObject(const std::wstring& name)
		: Entity(name), mState(Active)
	{
		mComponents.resize(Enums::COMPONENTTYPE::END);
	}

	inline void GameObject::Initialize()
	{
		for (auto comp : mComponents)
		{
			if (const auto ptr = comp.lock()) ptr->Initialize();
		}
	}

	inline void GameObject::AddComponent(const std::weak_ptr<Component>& component)
	{
		const int myOrder = component.lock()->GetUpdateOrder();
		mComponents[myOrder] = component;
		auto ptr = GetPtr();
		mComponents[myOrder].lock()->mOwner = std::static_pointer_cast<GameObject>(ptr);
	}

	inline void GameObject::Update()
	{
		for (auto comp : mComponents)
		{
			if (const auto ptr = comp.lock()) ptr->Update();
		}
	}

	inline void GameObject::FixedUpdate()
	{
		for (auto comp : mComponents)
		{
			if (const auto ptr = comp.lock()) ptr->FixedUpdate();
		}
	}

	inline void GameObject::Render()
	{
		for (auto comp : mComponents)
		{
			if (const auto ptr = comp.lock()) ptr->Render();
		}
	}
}
