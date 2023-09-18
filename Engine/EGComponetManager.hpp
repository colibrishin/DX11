#pragma once
#include "pch.h"

#include <map>
#include "EGResource.hpp"
#include "EGScene.hpp"

namespace Engine::Manager
{
	class ComponentManager
	{
	public:
		ComponentManager() = delete;
		~ComponentManager() = delete;

		template <typename T, typename... Args>
		static std::weak_ptr<T> Create(Args... args)
		{
			auto comp = std::make_shared<T>(args...);

			mComponents.insert({std::to_wstring(comp->GetID()), comp});

			return comp;
		}

	private:
		inline static std::map<std::wstring, std::shared_ptr<Abstract::Component>> mComponents{};
	};
}
