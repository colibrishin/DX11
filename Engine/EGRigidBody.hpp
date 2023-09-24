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
			const SimpleMath::Vector3& top_left,
			const SimpleMath::Vector3& bottom_right);

		RigidBody(const RigidBody& other) = default;
		~RigidBody() override;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		bool IsGravity() const;
		bool IsGrounded() const;

		void OnCollision(RigidBody* other);
		void OnCollisionExit();

	private:
		friend class Engine::Manager::CollisionManager;

		void UpdatePosition(const SimpleMath::Vector3& center);
		SimpleMath::Vector3 GetCenter();

		const SimpleMath::Vector3 m_top_left_;
		const SimpleMath::Vector3 m_bottom_right_;

		std::unique_ptr<BoundingBox> m_bounding_box_;

		SimpleMath::Vector3	m_velocity_;
		SimpleMath::Vector3 m_acceleration_;

		bool m_bGravity_;
		bool m_bGrounded_;
		bool m_bCollided_;
	};
}
