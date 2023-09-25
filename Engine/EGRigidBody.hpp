#pragma once
#include "EGComponetManager.hpp"
#include "EGGameObject.hpp"
#include "EGTransform.hpp"

namespace Engine::Abstract
{
	using namespace DirectX;

	class RigidBody : public Abstract::GameObject
	{
	public:
		RigidBody(const RigidBody& other) = default;
		RigidBody(const std::wstring& name, bool gravity, const SimpleMath::Vector3& position,
		          const std::weak_ptr<Mesh>& mesh);
		~RigidBody() override;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void SetPosition(const SimpleMath::Vector3& center);

		SimpleMath::Vector3 GetSize() const;
		SimpleMath::Vector3 GetCenter() const;

		bool IsGravity() const;
		bool IsGrounded() const;

		virtual void OnCollision(RigidBody* other);
		virtual void OnCollisionExit(RigidBody* other);

		Enums::BOUNDINGTYPE GetBoundingType() const;
		void GetBoundingBox(BoundingOrientedBox& box) const;
		void GetBoundingSphere(BoundingSphere& sphere) const;

	private:
		friend class Engine::Manager::CollisionManager;

		BoundingBox m_bounding_box_;

		SimpleMath::Vector3	m_velocity_;
		SimpleMath::Vector3 m_acceleration_;

		bool m_bGravity_override_;
		bool m_bGravity_;
		bool m_bGrounded_;
		bool m_bCollided_;
	};
}
