#pragma once
#include "EGScene.hpp"
#include <map>

namespace Engine::Manager
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void SetScene(const std::wstring& name);
		template <typename T>
		static void AddScene(const std::wstring& name)
		{
			mScenes[name] = std::make_shared<T>();
			mScenes[name]->Initialize();
		}

	private:
		inline static std::map<std::wstring, std::shared_ptr<Abstract::Scene>> mScenes{};
		inline static std::weak_ptr<Abstract::Scene> mPlayScene{};
	};
}
