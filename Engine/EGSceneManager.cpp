#include "pch.h"
#include "EGSceneManager.hpp"

#include "EGComponetManager.hpp"
#include "EGMeshRenderer.hpp"

namespace Engine::Manager
{
	void SceneManager::Initialize()
	{
	}

	void SceneManager::Update()
	{
		mPlayScene.lock()->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mPlayScene.lock()->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mPlayScene.lock()->Render();
	}
	void SceneManager::SetScene(const std::wstring& name)
	{
		if (mScenes.contains(name))
		{
			mPlayScene = mScenes[name];
		}
	}
}
