#include "pch.h"
#include "EGScene.hpp"
#include "EGGameObjectManager.hpp"
#include "EGD3DDevice.hpp"
#include "EGCommon.hpp"

namespace Engine::Abstract
{
	Scene::Scene(const std::wstring& name) : Entity(name), m_camera_(
		Manager::GameObjectManager::Add<Object::Camera>(name + L" Camera"))
	{
	}

	void Scene::Initialize()
	{
		m_world_ = SimpleMath::Matrix::CreateWorld(
			SimpleMath::Vector3::Zero,
			FORWARD,
			UP);

		m_ortho_ = XMMatrixOrthographicLH(
			Graphics::D3DDevice::GetDevice()->GetWidth(),
			Graphics::D3DDevice::GetDevice()->GetHeight(),
			nearZ,
			farZ);
		m_projection_ = XMMatrixPerspectiveFovLH(
			fov,
			Graphics::D3DDevice::GetDevice()->GetAspectRatio(), nearZ, farZ);
		m_camera_.lock()->SetPosition({ 0.0f, 0.0f, 5.0f });

		//m_light_.lock()->SetDiffuseColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		//m_light_.lock()->SetDirection(DirectX::SimpleMath::Vector3::Backward);

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

	void Scene::Render()
	{
		m_camera_.lock()->Render();

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

	void Scene::GetSceneCoordination(XMMATRIX& view, XMMATRIX& projection) const
	{
		m_camera_.lock()->GetViewMatrix(view);
		projection = m_projection_;
	}
}
