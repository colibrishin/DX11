#include "pch.h"
#include "EGRigidBody.hpp"

#include "EGDeltaTime.hpp"
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
		GetBoundingBoxFromMesh(m_boundingBox_, mesh);
		m_boundingBox_.Center = position;

		SetPosition(m_boundingBox_.Center);
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

		if (m_bGravity_ && m_bGravity_override_)
		{
			auto position = GetCenter();
			position.y -= GRAVITY_ACCEL * DeltaTime::GetDeltaTime()->GetElapsedSeconds();
			SetPosition(position);
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
		return SimpleMath::Vector3(m_boundingBox_.Extents) * 2.0f;
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
				0, -1.0f, 0};

			BoundingBox nextTBB = m_boundingBox_;
			nextTBB.Center = nextT;

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

	void RigidBody::SetPosition(const SimpleMath::Vector3& center)
	{
		const auto transform = GetComponent<Engine::Component::Transform>().lock();
		transform->SetPosition(center);
		m_boundingBox_.Center = center;
	}

	SimpleMath::Vector3 RigidBody::GetCenter() const
	{
		const auto transform = GetComponent<Engine::Component::Transform>().lock();
		return transform->GetPosition();
	}

	void RigidBody::GetBoundingBox(BoundingBox& box) const
	{
		box = m_boundingBox_;
	}
}
