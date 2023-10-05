#pragma once
#include "pch.h"
#include <execution>
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
			auto iter = std::find_if(
				std::execution::par_unseq,
				mObjects.begin(),
				mObjects.end(),
				[&](const auto& pair)
				{
					return pair.second->GetName() == name;
				}
			);

			return iter != mObjects.end() ? std::dynamic_pointer_cast<T>(iter->second) : std::weak_ptr<T>{};
		}

		template <typename T>
		static std::weak_ptr<T> Find(UINT id)
		{
			auto iter = mObjects.find(id);

			if (iter != mObjects.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			return {};
		}

		template <typename T = Abstract::GameObject>
		static std::weak_ptr<T> Add(const std::wstring& name)
		{
			std::weak_ptr<T> object = Find<T>(name);

			if (object.lock())
			{
				return object;
			}

			std::shared_ptr<T> generated = std::make_shared<T>(name);

			mObjects.emplace(generated->GetID(), generated);
			mObjects[generated->GetID()]->Initialize();

			return std::dynamic_pointer_cast<T>(mObjects[generated->GetID()]);
		}

		static void Remove(UINT id)
		{
			mObjects.erase(id);
		}

	private:
		inline static std::map<UINT, std::shared_ptr<Abstract::GameObject>> mObjects{};
	};
}
