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
		std::weak_ptr<T> GetComponent() const
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
		void Destroy();
		eState GetState() const;

	private:
		eState mState;
		std::vector<std::weak_ptr<Component>> mComponents{};
	};
}
