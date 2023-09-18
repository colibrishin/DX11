#pragma once
#include "../Engine/EGGameObject.hpp"
#include "../Engine/EGComponetManager.hpp"
#include "../Engine/EGTransform.hpp"
#include "../Engine/EGMeshRenderer.hpp"
#include "../Engine/EGDefaultPixelShader.hpp"
#include "../Engine/EGDefaultVertexShader.hpp"
#include "../Engine/EGResourceManager.hpp"
#include "../Engine/EGTrianlge.hpp"
#include "../Engine/EGDeltaTime.hpp"

namespace Client::Object
{
	class TestObject final : public Engine::Abstract::GameObject
	{
	public:
		TestObject(std::wstring name);
		~TestObject() override = default;
		inline void Initialize() override;
		inline void Update() override;
		inline void FixedUpdate() override;
		inline void Render() override;

		void move_up();
		void move_down();
		void move_left();
		void move_right();

		void scale_up();
		void scale_down();
	};

	inline TestObject::TestObject(std::wstring name) : GameObject(std::move(name))
	{
	}

	inline void TestObject::Initialize()
	{
		GameObject::Initialize();

		const auto tr = Engine::Manager::ComponentManager::Create<Engine::Abstract::Transform>();
		tr.lock()->SetPosition({0.0f, 0.0f, 0.0f});
		AddComponent(tr);

		const auto mesh = Engine::Manager::ResourceManager::Load<Engine::Mesh::TriangleMesh>(
			L"TriangleMesh");
		const auto ps = Engine::Manager::ResourceManager::Load<Engine::Shader::DefaultPixelShader>(
			L"DefaultPS");
		const auto vs = Engine::Manager::ResourceManager::Load<Engine::Shader::DefaultVertexShader>(
			L"DefaultVS");
		const auto meshRenderer = 
			Engine::Manager::ComponentManager::Create<Engine::MeshRenderer>().lock();

		meshRenderer->SetMesh(mesh);
		meshRenderer->SetShader(ps);
		meshRenderer->SetShader(vs);

		AddComponent(meshRenderer);
	}

	inline void TestObject::Update()
	{
		GameObject::Update();
	}

	inline void TestObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	inline void TestObject::Render()
	{
		GameObject::Render();
	}

	inline void TestObject::move_up()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {0, 10.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), 0};
		tr->SetPosition(pos);
	}

	inline void TestObject::move_down()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {0, -10.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), 0};
		tr->SetPosition(pos);
	}

	inline void TestObject::move_left()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {-10.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), -0.0f, 0};
		tr->SetPosition(pos);
	}

	inline void TestObject::move_right()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetPosition();
		pos += {10.0f * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds(), -0.0f, 0};
		tr->SetPosition(pos);
	}

	inline void TestObject::scale_up()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetScale();
		pos += {0.25f, 0.25f, 0.25f} * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds();
		tr->SetScale(pos);
	}

	inline void TestObject::scale_down()
	{
		const auto tr = GetComponent<Engine::Abstract::Transform>().lock();
		auto pos = tr->GetScale();
		pos -= {0.25f, 0.25f, 0.25f} * Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds();
		tr->SetScale(pos);
	}
}
