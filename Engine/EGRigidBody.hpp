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
		RigidBody(
			const std::wstring& name,
			bool gravity,
			const SimpleMath::Vector3& center,
			const SimpleMath::Vector3& size);

		RigidBody(const RigidBody& other) = default;
		~RigidBody() override;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		SimpleMath::Vector3 GetSize() const;

		bool IsGravity() const;
		bool IsGrounded() const;

		void OnCollision(RigidBody* other);
		void OnCollisionExit();

	private:
		friend class Engine::Manager::CollisionManager;

		void UpdatePosition(const SimpleMath::Vector3& center) const;
		SimpleMath::Vector3 GetCenter() const;
		void GetBoundingBox(BoundingBox& box) const;

		const SimpleMath::Vector3 m_size_;

		SimpleMath::Vector3	m_velocity_;
		SimpleMath::Vector3 m_acceleration_;

		bool m_bGravity_override_;
		bool m_bGravity_;
		bool m_bGrounded_;
		bool m_bCollided_;
	};
}
