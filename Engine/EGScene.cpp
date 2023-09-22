#include "pch.h"
#include "EGScene.hpp"
#include "EGGameObjectManager.hpp"
#include "EGD3DDevice.hpp"
#include "EGCommon.hpp"

namespace Engine::Abstract
{
	Scene::Scene(const std::wstring& name) : Entity(name), m_camera_(
		Manager::GameObjectManager::Add<Object::Camera>(name + L" Camera")),
		m_light_(Manager::GameObjectManager::Add<Object::Light>(name + L" Light"))
	{
	}

	void Scene::Initialize()
	{
		m_world_ = XMMatrixIdentity();
		m_ortho_ = XMMatrixOrthographicLH(
			Graphics::D3DDevice::GetDevice()->GetWidth(),
			Graphics::D3DDevice::GetDevice()->GetHeight(),
			nearZ,
			farZ);
		m_projection_ = XMMatrixPerspectiveFovLH(
			fov,
			Graphics::D3DDevice::GetDevice()->GetAspectRatio(), nearZ, farZ);
		m_camera_.lock()->SetPosition({ 0.0f, 0.0f, -5.0f });

		m_light_.lock()->SetDiffuseColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		m_light_.lock()->SetDirection(DirectX::SimpleMath::Vector3::Backward);

		for(auto& ly : mLayers)
		{
			ly.Initialize();
		}
	}

	void Scene::Update()
	{
		for(auto& ly : mLayers)
		{
			ly.Update();
		}
	}

	void Scene::FixedUpdate()
	{
		for(auto& ly : mLayers)
		{
			ly.FixedUpdate();
		}
	}

	void Scene::Transpose(Renderer::PerspectiveMatrix& perspective_matrix)
	{
		perspective_matrix.world = XMMatrixTranspose(perspective_matrix.world);
		perspective_matrix.view = XMMatrixTranspose(perspective_matrix.view);
		perspective_matrix.projection = XMMatrixTranspose(perspective_matrix.projection);
	}

	void Scene::Render()
	{
		m_camera_.lock()->Render();
		UpdateBuffer(m_matrix_buffer_);
		// TODO:
		// Make sure to transpose "matrices" before sending them into the shader, this is a requirement for DirectX 11. 
		// But why?
		Transpose(m_matrix_buffer_);

		const auto buffer = Renderer::constantBuffers[(UINT)Graphics::CBTYPES::PERSPECTIVE];
		buffer->Bind(&m_matrix_buffer_);
		buffer->SetPipeline(Graphics::ShaderStage::VS);

		const auto light = Renderer::constantBuffers[(UINT)Graphics::CBTYPES::LIGHT];
		light->Bind(&m_light_.lock()->GetLightBuffer());
		light->SetPipeline(Graphics::ShaderStage::PS);

		for(auto& ly : mLayers)
		{
			ly.Render();
		}
	}

	void Scene::AddGameObject(const std::weak_ptr<GameObject>& gameObject, UINT layerIndex)
	{
		mLayers[layerIndex].AddGameObject(gameObject);
	}

	void Scene::RemoveGameObject(const std::weak_ptr<GameObject>& gameObject, UINT layerIndex)
	{
		mLayers[layerIndex].RemoveGameObject(gameObject);
	}

	void Scene::UpdateBuffer(Renderer::PerspectiveMatrix& buffer) const
	{
		buffer.world = m_world_;
		m_camera_.lock()->GetViewMatrix(buffer.view);
		buffer.projection = m_projection_;
	}
}
