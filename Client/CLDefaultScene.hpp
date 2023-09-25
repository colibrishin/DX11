#pragma once
#include "pch.h"
#include <vector>

#include "CLBurgerObject.hpp"
#include "CLPlaneObject.hpp"
#include "CLSphereObject.hpp"
#include "../Engine/EGScene.hpp"
#include "../Engine/EGGameObjectManager.hpp"
#include "../Engine/EGDeltaTime.hpp"

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
		std::weak_ptr<Engine::Abstract::GameObject> m_burger_;
		std::weak_ptr<Engine::Abstract::GameObject> m_plane_;
		std::weak_ptr<Engine::Abstract::GameObject> m_sphere_;
	};

	inline void DefaultScene::Initialize()
	{
		Scene::Initialize();
		m_camera_.lock()->SetPosition({ 0.0f, 30.0f, 200.0f });

		m_plane_ = Engine::Manager::GameObjectManager::Add<Object::PlaneObject>(L"Plane");
		AddGameObject(m_plane_, Engine::Enums::LAYER::NONE);

		m_burger_ = Engine::Manager::GameObjectManager::Add<Object::BurgerObject>(L"Burger");
		AddGameObject(m_burger_, Engine::Enums::LAYER::NONE);

		m_sphere_ = Engine::Manager::GameObjectManager::Add<Object::SphereObject>(L"Sphere");
		AddGameObject(m_sphere_, Engine::Enums::LAYER::NONE);
	}

	inline void DefaultScene::Update()
	{
		Scene::Update();

		const auto obj = std::dynamic_pointer_cast<Object::BurgerObject>(m_burger_.lock());
		const auto key = Application::GetKeyState();


		if(key.W)
		{
			obj->move_up();
		}
		if (key.S)
		{
			obj->move_down();
		}
		if (key.A)
		{
			obj->move_left();
		}
		if (key.D)
		{
			obj->move_right();
		}
	}
}
