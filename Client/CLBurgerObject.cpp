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
		name, true, true, 20.0f, 10.0f, {}, Engine::Manager::ResourceManager::Load<Client::Mesh::TestBurgerMesh>(
			L"BurgerMesh"))
	{
	}

	void BurgerObject::Initialize()
	{
		RigidBody::Initialize();
	}

	void BurgerObject::Update()
	{
		m_velocity_.Clamp(DirectX::SimpleMath::Vector3::One * -30.0f, DirectX::SimpleMath::Vector3::One * 30.0f);

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
		m_velocity_ += DirectX::SimpleMath::Vector3::Up * 30.0f;
		m_offset_ = DirectX::SimpleMath::Vector3::Up;
	}

	void BurgerObject::move_down()
	{
		m_velocity_ += DirectX::SimpleMath::Vector3::Down * 30.0f;
		m_offset_ = DirectX::SimpleMath::Vector3::Down;
	}

	void BurgerObject::move_left()
	{
		m_velocity_ += DirectX::SimpleMath::Vector3::Left * 30.0f;
		m_offset_ = DirectX::SimpleMath::Vector3::Left;
	}

	void BurgerObject::move_right()
	{
		m_velocity_ += DirectX::SimpleMath::Vector3::Right * 30.0f;
		m_offset_ = DirectX::SimpleMath::Vector3::Right;
	}

	void BurgerObject::stop()
	{
		m_velocity_ = DirectX::SimpleMath::Vector3::Zero;
		m_offset_ = DirectX::SimpleMath::Vector3::Zero;
	}
}
