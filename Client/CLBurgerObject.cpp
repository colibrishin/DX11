#include "pch.h"
#include "CLBurgerObject.hpp"

#include "CLExampleCupObject.hpp"
#include "CLExampleCupMesh.hpp"
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
		name, true, {5.0f, 5.0f, 5.0f}, { 10.0f, 10.0f, 10.0f })
	{
	}

	void BurgerObject::Initialize()
	{
		RigidBody::Initialize();

		const auto mesh = Engine::Manager::ResourceManager::Load<Client::Mesh::TestBurgerMesh>(
			L"BurgerMesh");

		const auto meshRenderer =
			Engine::Manager::ComponentManager::Create<Engine::MeshRenderer>(this).lock();

		meshRenderer->SetMesh(mesh);
		AddComponent(meshRenderer);
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
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {0, 30.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), 0};
		tr->SetPosition(pos);
		m_offset_ = DirectX::SimpleMath::Vector3::Up;
	}

	void BurgerObject::move_down()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {0, -30.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), 0};
		tr->SetPosition(pos);
		m_offset_ = DirectX::SimpleMath::Vector3::Down;
	}

	void BurgerObject::move_left()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {-30.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), -0.0f, 0};
		tr->SetPosition(pos);
		m_offset_ = DirectX::SimpleMath::Vector3::Left;
	}

	void BurgerObject::move_right()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {30.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), -0.0f, 0};
		tr->SetPosition(pos);
		m_offset_ = DirectX::SimpleMath::Vector3::Right;
	}
}
