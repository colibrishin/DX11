#include "pch.h"
#include "CLPlaneObject.hpp"

#include "CLExampleCupObject.hpp"

#include "CLExampleCupMesh.hpp"
#include "../Engine/EGGameObjectManager.hpp"
#include "../Engine/EGComponetManager.hpp"
#include "../Engine/EGResourceManager.hpp"
#include "../Engine/EGDeltaTime.hpp"
#include "../Engine/EGSceneManager.hpp"
#include "../Engine/EGMeshRenderer.hpp"
#include "../Engine/EGPlaneMesh.hpp"

namespace Client::Object
{
	PlaneObject::PlaneObject(const std::wstring& name) : RigidBody(
		name, false, {}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f})
	{
	}

	void PlaneObject::Initialize()
	{
		GameObject::Initialize();

		const auto tr = Engine::Manager::ComponentManager::Create<Engine::Abstract::Transform>(this);
		tr.lock()->SetPosition({ 0.0f, 0.0f, 0.0f });
		AddComponent(tr);

		const auto mesh = Engine::Manager::ResourceManager::Load<Engine::Mesh::PlaneMesh>(
			L"PlaneMesh");

		const auto meshRenderer =
			Engine::Manager::ComponentManager::Create<Engine::MeshRenderer>(this).lock();

		meshRenderer->SetMesh(mesh);
		AddComponent(meshRenderer);
	}

	void PlaneObject::Update()
	{
		GameObject::Update();
	}

	void PlaneObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void PlaneObject::Render()
	{
		GameObject::Render();
	}
}
