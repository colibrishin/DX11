#include "pch.h"
#include "EGLayer.hpp"

#include "EGGameObject.hpp"

namespace Engine::Abstract
{
	Layer::Layer() : Entity(L"test")
	{
	}

	void Layer::Initialize()
	{
		for (const auto gameObject : mGameObjects)
		{
			if (const auto obj = gameObject.lock())
			{
				obj->Initialize();
			}

		}
	}

	void Layer::Update()
	{
		for (const auto gameObject : mGameObjects)
		{
			if (const auto obj = gameObject.lock())
			{
				obj->Update();
			}
		}
	}

	void Layer::FixedUpdate()
	{
		for (const auto gameObject : mGameObjects)
		{
			if (const auto obj = gameObject.lock())
			{
				obj->FixedUpdate();
			}
		}
	}

	void Layer::Render()
	{
		for (const auto gameObject : mGameObjects)
		{
			if (const auto obj = gameObject.lock())
			{
				obj->Render();
			}
		}
	}

	void Layer::AddGameObject(const std::weak_ptr<GameObject>& gameObject)
	{
		mGameObjects.push_back(gameObject);
	}

	void Layer::RemoveGameObject(const std::weak_ptr<GameObject>& gameObject)
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
