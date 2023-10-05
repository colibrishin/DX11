#pragma once
#include <map>
#include "EGResource.hpp"
#include "EGScene.hpp"

namespace Engine::Manager
{
	class ResourceManager
	{
	public:
		ResourceManager() = delete;
		~ResourceManager() = delete;

		template <typename T>
		static std::weak_ptr<T> Find(const std::wstring& key)
		{
			auto iter = mResources.find(key);

			if (iter != mResources.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			return {};
		}

		template <typename T, typename... Args>
		static std::weak_ptr<T> Load(const std::wstring& key, Args... args)
		{
			auto resource = Find<T>(key);
			if (resource.lock())
			{
				return resource;
			}

			auto insertion = std::make_shared<T>(key, args...);
			insertion->Load();
			insertion->SetKey(key);
			mResources.insert({key, insertion});

			return insertion;
		}

		template <typename T>
		static void Insert(const std::wstring& key, T* resource)
		{
			mResources.insert({key, std::shared_ptr<T>(resource)});
		}

	private:
		inline static std::map<std::wstring, std::shared_ptr<Abstract::Resource>> mResources{};
	};
}
