#pragma once
#include "pch.h"
#include "CLStoneTexture.hpp"
#include "../Engine/EGGameObject.hpp"
#include "../Engine/EGComponetManager.hpp"
#include "../Engine/EGTransform.hpp"
#include "../Engine/EGMeshRenderer.hpp"
#include "../Engine/EGTextureVS.hpp"
#include "../Engine/EGTexturePS.hpp"
#include "../Engine/EGResourceManager.hpp"
#include "../Engine/EGTextureTriangleMesh.hpp"
#include "../Engine/EGSceneManager.hpp"
#include "../Engine/EGDeltaTime.hpp"
#include "../Engine/EGGameObjectManager.hpp"
#include "../Engine/EGCircleMesh.hpp"
#include "CLTestObejct.hpp"

namespace Client::Object
{
	class ProjectileTestObject final : public TestObject
	{
	public:
		ProjectileTestObject(const std::wstring& key);
		~ProjectileTestObject() override = default;
		inline void Initialize() override;
		inline void Update() override;
		inline void FixedUpdate() override;
		inline void Render() override;

		void SetOffset(DirectX::SimpleMath::Vector3 offset) { m_offset_ = offset; }

	private:
		float m_alive_time_;
	};

	inline ProjectileTestObject::ProjectileTestObject(const std::wstring& key) : TestObject(key), m_alive_time_(0.0f)
	{
	}

	inline void ProjectileTestObject::Initialize()
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

	inline void ProjectileTestObject::Update()
	{
		GameObject::Update();
		if(m_offset_ == DirectX::SimpleMath::Vector3::Up)
		{
			move_up();
		}
		else if(m_offset_ == DirectX::SimpleMath::Vector3::Down)
		{
			move_down();
		}
		else if(m_offset_ == DirectX::SimpleMath::Vector3::Left)
		{
			move_left();
		}
		else
		{
			move_right();
		}

		m_alive_time_ += Engine::DeltaTime::GetDeltaTime()->GetElapsedSeconds();

		if(m_alive_time_ > 1.0f)
		{
			Destroy();
		}
	}

	inline void ProjectileTestObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	inline void ProjectileTestObject::Render()
	{
		GameObject::Render();
	}
}
