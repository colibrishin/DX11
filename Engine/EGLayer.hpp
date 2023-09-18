#pragma once
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

	private:
		std::vector<std::weak_ptr<GameObject>> mGameObjects;
	};

	inline Layer::Layer() : Entity(L"test")
	{
	}

	inline void Layer::Initialize()
	{
		for (const auto gameObject : mGameObjects)
		{
			gameObject.lock()->Initialize();
		}
	}

	inline void Layer::Update()
	{
		for (const auto gameObject : mGameObjects)
		{
			gameObject.lock()->Update();
		}
	}

	inline void Layer::FixedUpdate()
	{
		for (const auto gameObject : mGameObjects)
		{
			gameObject.lock()->FixedUpdate();
		}
	}

	inline void Layer::Render()
	{
		for (const auto gameObject : mGameObjects)
		{
			gameObject.lock()->Render();
		}
	}

	inline void Layer::AddGameObject(const std::weak_ptr<GameObject>& gameObject)
	{
		mGameObjects.push_back(gameObject);
	}
}
