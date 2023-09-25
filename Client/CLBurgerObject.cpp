#include "pch.h"
#include "CLBurgerObject.hpp"

#include "CLTestHamburgerMesh.hpp"
#include "../Engine/EGGameObjectManager.hpp"
#include "../Engine/EGComponetManager.hpp"
#include "../Engine/EGResourceManager.hpp"
#include "../Engine/EGDeltaTime.hpp"
#include "../Engine/EGSceneManager.hpp"
#include "../Engine/EGMeshRenderer.hpp"

namespace Client::Object
{
	BurgerObject::BurgerObject(const std::wstring& name) : RigidBody(
		name, true, {}, Engine::Manager::ResourceManager::Load<Client::Mesh::TestBurgerMesh>(
			L"BurgerMesh"))
	{
	}

	void BurgerObject::Initialize()
	{
		RigidBody::Initialize();
	}

	void BurgerObject::Update()
	{
		RigidBody::Update();
	}

	void BurgerObject::FixedUpdate()
	{
		RigidBody::FixedUpdate();
	}

	void BurgerObject::Render()
	{
		RigidBody::Render();
	}

	void BurgerObject::move_up()
	{
		auto pos = GetCenter();
		pos += {0, 30.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), 0};
		SetPosition(pos);
		m_offset_ = DirectX::SimpleMath::Vector3::Up;
	}

	void BurgerObject::move_down()
	{
		auto pos = GetCenter();
		pos += {0, -30.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), 0};
		SetPosition(pos);
		m_offset_ = DirectX::SimpleMath::Vector3::Down;
	}

	void BurgerObject::move_left()
	{
		auto pos = GetCenter();
		pos += {-30.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), -0.0f, 0};
		SetPosition(pos);
		m_offset_ = DirectX::SimpleMath::Vector3::Left;
	}

	void BurgerObject::move_right()
	{
		auto pos = GetCenter();
		pos += {30.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), -0.0f, 0};
		SetPosition(pos);
		m_offset_ = DirectX::SimpleMath::Vector3::Right;
	}
}
