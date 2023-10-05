#pragma once
#include "EGCollisionManager.hpp"
#include "EGGameObject.hpp"

namespace Engine::Abstract
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer() override = default;

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(const std::weak_ptr<GameObject>& gameObject);
		void RemoveGameObject(const std::weak_ptr<GameObject>& gameObject);

	private:
		friend class Engine::Manager::CollisionManager;

		std::vector<std::weak_ptr<GameObject>> mGameObjects;
	};
}
