#include "pch.h"
#include "CLPlaneObject.hpp"

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
		name, false, {}, Engine::Manager::ResourceManager::Load<Engine::Mesh::PlaneMesh>(
			L"PlaneMesh", DirectX::SimpleMath::Vector3{100.0f, 1.0f, 100.0f}))
	{
	}

	void PlaneObject::Initialize()
	{
		RigidBody::Initialize();
	}

	void PlaneObject::Update()
	{
		RigidBody::Update();
	}

	void PlaneObject::FixedUpdate()
	{
		RigidBody::FixedUpdate();
	}

	void PlaneObject::Render()
	{
		RigidBody::Render();
	}
}
