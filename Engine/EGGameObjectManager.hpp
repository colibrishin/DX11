#pragma once
#include "pch.h"
#include <map>
#include "EGResource.hpp"
#include "EGScene.hpp"

namespace Engine::Manager
{
	class GameObjectManager
	{
	public:
		GameObjectManager() = delete;
		~GameObjectManager() = delete;

		template <typename T>
		static std::weak_ptr<T> Find(const std::wstring& name)
		{
			auto iter = mObjects.find(name);

			if (iter != mObjects.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			return {};
		}

		template <typename T>
		static std::weak_ptr<T> Add(const std::wstring& name)
		{
			std::weak_ptr<T> object = Find<T>(name);
			if (object.lock())
			{
				return object;
			}

			auto insertion = std::make_shared<T>(name);
			insertion->Initialize();
			mObjects.insert({name, insertion});

			return insertion;
		}

	private:
		inline static std::map<std::wstring, std::shared_ptr<Abstract::GameObject>> mObjects{};
	};
}
