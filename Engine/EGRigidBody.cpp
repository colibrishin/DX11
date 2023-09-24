#include "pch.h"
#include "EGRigidBody.hpp"

#include "EGDeltaTime.hpp"

namespace Engine::Abstract
{
	RigidBody::RigidBody(
		const std::wstring& name, 
		bool gravity,
		const SimpleMath::Vector3& center,
		const SimpleMath::Vector3& top_left,
		const SimpleMath::Vector3& bottom_right) :
		GameObject(name),
		m_top_left_(top_left),
		m_bottom_right_(bottom_right),
		m_bounding_box_(nullptr),
		m_bGravity_(gravity),
		m_bGrounded_(false)
	{
		AddComponent(
			Manager::ComponentManager::Create<Abstract::Transform>(this));
		m_bounding_box_ = std::make_unique<BoundingBox>();
		BoundingBox::CreateFromPoints(*m_bounding_box_.get(), m_top_left_, m_bottom_right_);
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

		if (m_bGravity_)
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
		const float y = GetCenter().y;
		const float y_p = other->GetCenter().y;
		const float delta = std::abs(y - y_p);

		if (delta <= 1.0f)
		{
			m_bGrounded_ = true;
			m_bGravity_ = false;
		}
		else
		{
			m_bGrounded_ = false;
			m_bGravity_ = true;
		}
	}

	void RigidBody::OnCollisionExit()
	{
	}

	void RigidBody::UpdatePosition(const SimpleMath::Vector3& center)
	{
		m_bounding_box_->Center = center;

		const auto transform = GetComponent<Abstract::Transform>().lock();
		transform->SetPosition(center);
	}

	SimpleMath::Vector3 RigidBody::GetCenter()
	{
		const auto transform = GetComponent<Abstract::Transform>().lock();
		return transform->GetPosition();
	}
}
