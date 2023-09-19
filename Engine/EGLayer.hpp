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
		void RemoveGameObject(const std::weak_ptr<GameObject>& gameObject);

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
			if(const auto obj = gameObject.lock())
			{
				obj->Initialize();
			}
				
		}
	}

	inline void Layer::Update()
	{
		for (const auto gameObject : mGameObjects)
		{
			if(const auto obj = gameObject.lock())
			{
				obj->Update();
			}
		}
	}

	inline void Layer::FixedUpdate()
	{
		for (const auto gameObject : mGameObjects)
		{
			if(const auto obj = gameObject.lock())
			{
				obj->FixedUpdate();
			}
		}
	}

	inline void Layer::Render()
	{
		for (const auto gameObject : mGameObjects)
		{
			if(const auto obj = gameObject.lock())
			{
				obj->Render();
			}
		}
	}

	inline void Layer::AddGameObject(const std::weak_ptr<GameObject>& gameObject)
	{
		mGameObjects.push_back(gameObject);
	}

	inline void Layer::RemoveGameObject(const std::weak_ptr<GameObject>& gameObject)
	{
		std::erase_if(
			mGameObjects,
			[gameObject](const std::weak_ptr<GameObject>& vObj)
			{
				return vObj.lock() == gameObject.lock();
			}
		);
	}
}
