#include "pch.h"
#include "EGRigidBody.hpp"

#include "EGDeltaTime.hpp"
#include "EGGameObjectManager.hpp"
#include "EGMesh.hpp"
#include "EGMeshRenderer.hpp"
#include "EGScript.hpp"

namespace Engine::Abstract
{
	RigidBody::RigidBody(
		const std::wstring& name, 
		bool gravity,
		const SimpleMath::Vector3& position,
		const std::weak_ptr<Mesh>& mesh) :
		GameObject(name),
		m_bGravity_override_(gravity),
		m_bGravity_(gravity),
		m_bGrounded_(false),
		m_bCollided_(false)
	{
		AddComponent(
			Manager::ComponentManager::Create<Engine::Component::Transform>(this));

		const auto meshRenderer = Manager::ComponentManager::Create<Engine::Component::MeshRenderer>(this);
		meshRenderer.lock()->SetMesh(mesh);

		AddComponent(meshRenderer);

		meshRenderer.lock()->GetBoundingBox(m_bounding_box_);
		SetPosition(position);
	}

	RigidBody::~RigidBody()
	{
		Manager::ComponentManager::Remove(GetComponent<Engine::Component::Transform>().lock()->GetID());
		Manager::ComponentManager::Remove(GetComponent<Engine::Component::MeshRenderer>().lock()->GetID());
	}

	void RigidBody::Initialize()
	{
		GameObject::Initialize();
	}

	void RigidBody::Update()
	{
		GameObject::Update();

		if (GetState() == Paused)
		{
			return;
		}

		if (m_bGravity_override_)
		{
			if(m_bGravity_)
			{
				auto position = GetCenter();
				position.y -= GRAVITY_ACCEL * DeltaTime::GetDeltaTime()->GetElapsedSeconds();

				SetPosition(position);
			}
		}
	}

	void RigidBody::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void RigidBody::Render()
	{
		GameObject::Render();
	}

	SimpleMath::Vector3 RigidBody::GetSize() const
	{
		return SimpleMath::Vector3(m_bounding_box_.Extents) * 2.0f;
	}

	bool RigidBody::IsGravity() const
	{
		return m_bGravity_;
	}

	bool RigidBody::IsGrounded() const
	{
		return m_bGrounded_;
	}

	void RigidBody::OnCollision(RigidBody* other)
	{
	}

	void RigidBody::OnCollisionExit(RigidBody* other)
	{
	}

	Enums::BOUNDINGTYPE RigidBody::GetBoundingType() const
	{
		const auto renderer = GetComponent<Engine::Component::MeshRenderer>().lock();
		return renderer->GetBoundingType();
	}

	void RigidBody::GetBoundingBox(BoundingOrientedBox& box) const
	{
		BoundingOrientedBox::CreateFromBoundingBox(box, m_bounding_box_);
		box.Orientation = GetComponent<Engine::Component::Transform>().lock()->GetRotation();
	}

	void RigidBody::GetBoundingSphere(BoundingSphere& sphere) const
	{
		// fixme: this is a workaround with not using x, y, z value directly
		SimpleMath::Vector3 magnitude = m_bounding_box_.Extents;
		SimpleMath::Viewport viewport {};
		SimpleMath::Vector3 projection;
		viewport.Project(magnitude, XMMatrixIdentity(), XMMatrixIdentity(), XMMatrixIdentity(), projection);
		sphere.Radius = projection.Length();
		sphere.Center = GetComponent<Engine::Component::Transform>().lock()->GetPosition();
	}

	void RigidBody::SetPosition(const SimpleMath::Vector3& center)
	{
		const auto transform = GetComponent<Engine::Component::Transform>().lock();
		transform->SetPosition(center);
		m_bounding_box_.Center = center;
	}

	SimpleMath::Vector3 RigidBody::GetCenter() const
	{
		const auto transform = GetComponent<Engine::Component::Transform>().lock();
		return transform->GetPosition();
	}
}
