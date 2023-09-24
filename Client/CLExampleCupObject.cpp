#include "pch.h"
#include "CLExampleCupObject.hpp"

#include "CLExampleCupMesh.hpp"
#include "../Engine/EGGameObjectManager.hpp"
#include "../Engine/EGComponetManager.hpp"
#include "../Engine/EGResourceManager.hpp"
#include "../Engine/EGDeltaTime.hpp"
#include "../Engine/EGSceneManager.hpp"
#include "../Engine/EGMeshRenderer.hpp"

namespace Client::Object
{
	ExampleCupObject::ExampleCupObject(const std::wstring& name) : GameObject(name)
	{
	}

	void ExampleCupObject::Initialize()
	{
		GameObject::Initialize();

		const auto tr = Engine::Manager::ComponentManager::Create<Engine::Abstract::Transform>(this);
		tr.lock()->SetPosition({ 0.0f, 0.0f, 0.0f });
		AddComponent(tr);

		const auto mesh = Engine::Manager::ResourceManager::Load<Client::Mesh::ExampleCupMesh>(
			L"CupMesh");

		const auto meshRenderer =
			Engine::Manager::ComponentManager::Create<Engine::MeshRenderer>(this).lock();

		meshRenderer->SetMesh(mesh);
		AddComponent(meshRenderer);
	}

	void ExampleCupObject::Update()
	{
		GameObject::Update();
	}

	void ExampleCupObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void ExampleCupObject::Render()
	{
		GameObject::Render();
	}

	void ExampleCupObject::move_up()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {0, 10.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), 0};
		tr->SetPosition(pos);
		m_offset_ = DirectX::SimpleMath::Vector3::Up;
	}

	void ExampleCupObject::move_down()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {0, -10.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), 0};
		tr->SetPosition(pos);
		m_offset_ = DirectX::SimpleMath::Vector3::Down;
	}

	void ExampleCupObject::move_left()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {-10.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), -0.0f, 0};
		tr->SetPosition(pos);
		m_offset_ = DirectX::SimpleMath::Vector3::Left;
	}

	void ExampleCupObject::move_right()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {10.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), -0.0f, 0};
		tr->SetPosition(pos);
		m_offset_ = DirectX::SimpleMath::Vector3::Right;
	}
}
