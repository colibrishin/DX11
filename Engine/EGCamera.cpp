#include "pch.h"
#include "EGCamera.hpp"

#include "EGComponetManager.hpp"
#include "EGTransform.hpp"

namespace Engine::Object
{
	Camera::Camera(const std::wstring& name) : GameObject(name), m_view_matrix_()
	{
	}

	Camera::~Camera() = default;

	void Camera::Initialize()
	{
		const auto tr = Manager::ComponentManager::Create<Abstract::Transform>(this).lock();
		AddComponent(tr);
	}

	void Camera::SetPosition(SimpleMath::Vector3 position)
	{
		// TODO: Lerp movement
		// https://github.com/microsoft/DirectXTK/wiki/Basic-game-math#moving-the-camera
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
		const XMFLOAT3 up = SimpleMath::Vector3::Up;
		const XMFLOAT3 lookAt = SimpleMath::Vector3::Forward;

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
		
		m_view_matrix_ = XMMatrixLookAtRH(positionVector, lookAtVector, upVector);
	}

	void Camera::GetViewMatrix(XMMATRIX& view) const
	{
		view = m_view_matrix_;
	}
}
