#include "pch.h"
#include "EGRigidBody.hpp"

#include "EGDeltaTime.hpp"

namespace Engine::Abstract
{
	RigidBody::RigidBody(
		const std::wstring& name, 
		bool gravity,
		const SimpleMath::Vector3& center,
		const SimpleMath::Vector3& size) :
		GameObject(name),
		m_size_(size),
		m_bGravity_override_(gravity),
		m_bGravity_(gravity),
		m_bGrounded_(false),
		m_bCollided_(false)
	{
		AddComponent(
			Manager::ComponentManager::Create<Abstract::Transform>(this));

		UpdatePosition(center);
	}

	RigidBody::~RigidBody()
	{
		Manager::ComponentManager::Remove(GetComponent<Abstract::Transform>().lock()->GetID());
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

		if (m_bGravity_ && m_bGravity_override_)
		{
			auto position = GetCenter();
			position.y -= GRAVITY_ACCEL * DeltaTime::GetDeltaTime()->GetElapsedSeconds();
			UpdatePosition(position);
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
		return m_size_;
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
		if(m_bGravity_override_)
		{
			const auto nextT = GetCenter() + SimpleMath::Vector3{
				0, -GRAVITY_ACCEL * DeltaTime::GetDeltaTime()->GetElapsedSeconds(), 0};

			BoundingBox nextTBB;
			BoundingBox::CreateFromPoints(
				nextTBB, 
				nextT + (GetSize() / 2), 
				nextT - (GetSize() / 2));

			BoundingBox bb;
			other->GetBoundingBox(bb);

			if(bb.Intersects(nextTBB))
			{
				m_bGrounded_ = true;
				m_bGravity_ = false;
			}
		}
	}

	void RigidBody::OnCollisionExit()
	{
		if(!m_bGravity_)
		{
			m_bGrounded_ = false;
			m_bGravity_ = true;
		}
	}

	void RigidBody::UpdatePosition(const SimpleMath::Vector3& center) const
	{
		const auto transform = GetComponent<Abstract::Transform>().lock();
		transform->SetPosition(center);
	}

	SimpleMath::Vector3 RigidBody::GetCenter() const
	{
		const auto transform = GetComponent<Abstract::Transform>().lock();
		return transform->GetPosition();
	}

	void RigidBody::GetBoundingBox(BoundingBox& box) const
	{
		BoundingBox::CreateFromPoints(
			box, 
			GetCenter() + (GetSize() / 2), 
			GetCenter() - (GetSize() / 2));
	}
}
