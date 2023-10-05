#include "pch.h"
#include "CLSphereObject.hpp"

#include "../Engine/EGGameObjectManager.hpp"
#include "../Engine/EGComponetManager.hpp"
#include "../Engine/EGResourceManager.hpp"
#include "../Engine/EGDeltaTime.hpp"
#include "../Engine/EGSceneManager.hpp"
#include "../Engine/EGMeshRenderer.hpp"
#include "../Engine/EGSphereMesh.hpp"

namespace Client::Object
{
	SphereObject::SphereObject(const std::wstring& name) : RigidBody(
		name, false, true, 1000.0f, 5.0f, {}, Engine::Manager::ResourceManager::Load<Engine::Mesh::SphereMesh>(
			L"SphereMesh", 10.0f))
	{
	}

	void SphereObject::Initialize()
	{
		RigidBody::Initialize();
	}

	void SphereObject::Update()
	{
		RigidBody::Update();
	}

	void SphereObject::FixedUpdate()
	{
		RigidBody::FixedUpdate();
	}

	void SphereObject::Render()
	{
		RigidBody::Render();
	}
}
