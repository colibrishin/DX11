#include "pch.h"
#include "EGCamera.hpp"

#include "EGComponetManager.hpp"
#include "EGTransform.hpp"

namespace Engine::Object
{
	Camera::Camera(const std::wstring& name) : GameObject(name), m_view_matrix_()
	{
		const auto tr = Manager::ComponentManager::Create<Abstract::Transform>().lock();
		AddComponent(tr);
	}

	Camera::~Camera()
	{
		Destroy();
	}

	void Camera::SetPosition(SimpleMath::Vector3 position)
	{
		const auto tr = GetComponent<Abstract::Transform>().lock();
		tr->SetPosition(position);
	}

	void Camera::SetRotation(SimpleMath::Vector3 rotation)
	{
		const auto tr = GetComponent<Abstract::Transform>().lock();
		tr->SetRotation(rotation);
	}

	void Camera::Render()
	{
		GameObject::Render();
		const XMFLOAT3 up {0.0f, 0.1f, 0.0f};
		const XMFLOAT3 lookAt {0.0f, 0.0f, 1.0f};

		const auto tr = GetComponent<Abstract::Transform>().lock();
		const auto position = tr->GetPosition();
		const auto rotation = tr->GetRotation();

		XMVECTOR upVector = XMLoadFloat3(&up);
		XMVECTOR lookAtVector = XMLoadFloat3(&lookAt);
		const XMVECTOR positionVector = XMLoadFloat3(&position);
		const XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYawFromVector(rotation * 0.0174532925f);

		lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
		upVector = XMVector3TransformCoord(upVector, rotationMatrix);
		
		lookAtVector = XMVectorAdd(positionVector, lookAtVector);
		
		m_view_matrix_ = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
	}

	void Camera::GetViewMatrix(XMMATRIX& view) const
	{
		view = m_view_matrix_;
	}
}
