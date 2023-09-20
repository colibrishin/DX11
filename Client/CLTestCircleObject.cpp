#include "pch.h"
#include "CLTestCircleObject.hpp"

#include "CLTestObejct.hpp"
#include "../Engine/EGGameObjectManager.hpp"
#include "../Engine/EGComponetManager.hpp"
#include "../Engine/EGResourceManager.hpp"
#include "../Engine/EGTextureVS.hpp"
#include "../Engine/EGDeltaTime.hpp"
#include "CLProjectileTestObject.hpp"
#include "../Engine/EGSceneManager.hpp"
#include "../Engine/EGTextureSquareMesh.hpp"
#include "../Engine/EGDefaultPixelShader.hpp"
#include "../Engine/EGDefaultVertexShader.hpp"
#include "../Engine/EGSquareMesh.hpp"

namespace Client::Object
{
	TestCircleObject::TestCircleObject(const std::wstring& name) : GameObject(std::move(name))
	{
	}

	void TestCircleObject::Initialize()
	{
		GameObject::Initialize();

		const auto tr = Engine::Manager::ComponentManager::Create<Engine::Abstract::Transform>();
		tr.lock()->SetPosition({0.0f, 0.0f, 0.0f});
		AddComponent(tr);

		const auto mesh = Engine::Manager::ResourceManager::Load<Engine::Mesh::CircleMesh>(
			L"CircleMesh");
		const auto ps = Engine::Manager::ResourceManager::Load<Engine::Shader::DefaultPixelShader>(
			L"ColorPS");
		const auto vs = Engine::Manager::ResourceManager::Load<Engine::Shader::DefaultVertexShader>(
			L"ColorVS");

		const auto meshRenderer = 
			Engine::Manager::ComponentManager::Create<Engine::MeshRenderer<Engine::Renderer::Vertex>>().lock();

		meshRenderer->SetMesh(mesh);
		meshRenderer->SetShader(ps);
		meshRenderer->SetShader(vs);

		AddComponent(meshRenderer);
	}

	void TestCircleObject::Update()
	{
		GameObject::Update();
	}

	void TestCircleObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void TestCircleObject::Render()
	{
		GameObject::Render();
	}
}
