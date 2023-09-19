#include "pch.h"
#include "CLTestObejct.hpp"
#include "../Engine/EGGameObjectManager.hpp"
#include "../Engine/EGComponetManager.hpp"
#include "../Engine/EGResourceManager.hpp"
#include "../Engine/EGTextureVS.hpp"
#include "../Engine/EGDeltaTime.hpp"
#include "CLProjectileTestObject.hpp"
#include "../Engine/EGSceneManager.hpp"	

namespace Client::Object
{
	TestObject::TestObject(const std::wstring& name) : GameObject(std::move(name))
	{
	}

	void TestObject::Initialize()
	{
		GameObject::Initialize();

		const auto tr = Engine::Manager::ComponentManager::Create<Engine::Abstract::Transform>();
		tr.lock()->SetPosition({0.0f, 0.0f, 0.0f});
		AddComponent(tr);

		const auto mesh = Engine::Manager::ResourceManager::Load<Engine::Mesh::TextureTriangleMesh>(
			L"TriangleMesh");
		const auto ps = Engine::Manager::ResourceManager::Load<Engine::Shader::TexturePixelShader>(
			L"TexturePS");
		const auto vs = Engine::Manager::ResourceManager::Load<Engine::Shader::TextureVertexShader>(
			L"TextureVS");
		const auto tex = Engine::Manager::ResourceManager::Load<Texture::StoneTexture>(
			L"TestTexture");

		const auto meshRenderer = 
			Engine::Manager::ComponentManager::Create<Engine::MeshRenderer<Engine::Renderer::TextureVertex>>().lock();

		meshRenderer->SetMesh(mesh);
		meshRenderer->SetShader(ps);
		meshRenderer->SetShader(vs);
		meshRenderer->SetTexture(tex);

		AddComponent(meshRenderer);
	}

	void TestObject::Update()
	{
		GameObject::Update();
	}

	void TestObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void TestObject::Render()
	{
		GameObject::Render();
	}

	void TestObject::move_up()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {0, 10.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), 0};
		tr->SetPosition(pos);
		m_offset_ = up;
	}

	void TestObject::move_down()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {0, -10.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), 0};
		tr->SetPosition(pos);
		m_offset_ = down;
	}

	void TestObject::move_left()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {-10.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), -0.0f, 0};
		tr->SetPosition(pos);
		m_offset_ = left;
	}

	void TestObject::move_right()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {10.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), -0.0f, 0};
		tr->SetPosition(pos);
		m_offset_ = right;
	}

	void TestObject::scale_up()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetScale();
		pos += {0.25f, 0.25f, 0.25f} * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds();
		tr->SetScale(pos);
	}

	void TestObject::scale_down()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetScale();
		pos -= {0.25f, 0.25f, 0.25f} * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds();
		tr->SetScale(pos);
	}

	void TestObject::shoot()
	{
		static int count = 0;
		const auto prj = Engine::Manager::GameObjectManager::Add<ProjectileTestObject>(std::to_wstring(count));
		Engine::Manager::SceneManager::GetActiveScene().lock()->AddGameObject(std::dynamic_pointer_cast<GameObject>(prj.lock()), Engine::Enums::LAYER::NONE);
		prj.lock()->SetOffset(m_offset_);
		++count;
	}
}
