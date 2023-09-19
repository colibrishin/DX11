#pragma once
#include "pch.h"
#include <vector>
#include "../Engine/EGScene.hpp"
#include "../Engine/EGGameObjectManager.hpp"
#include "CLTestObejct.hpp"

namespace Client
{
	class DefaultScene : public Engine::Abstract::Scene
	{
	public:
		DefaultScene() : Scene(L"DefaultScene") {}
		~DefaultScene() override = default;

		void Initialize() override;
		void Update() override;

	private:
		std::weak_ptr<Engine::Abstract::GameObject> m_triangle_;
	};

	inline void DefaultScene::Initialize()
	{
		Scene::Initialize();

		m_triangle_ = Engine::Manager::GameObjectManager::Add<Object::TestObject>(L"Test");
		AddGameObject(m_triangle_, Engine::Enums::LAYER::NONE);
	}

	inline void DefaultScene::Update()
	{
		Scene::Update();
		const auto key = Application::GetKeyState();
		const auto cast = std::dynamic_pointer_cast<Object::TestObject>(m_triangle_.lock());

		if(key.W)
		{
			cast->move_up();
		}
		if(key.S)
		{
			cast->move_down();
		}
		if(key.A)
		{
			cast->move_left();
		}
		if(key.D)
		{
			cast->move_right();
		}
		if(key.Up)
		{
			cast->scale_up();
		}
		if(key.Down)
		{
			cast->scale_down();
		}
		if(key.Space)
		{
			cast->shoot();
		}
	}
}
