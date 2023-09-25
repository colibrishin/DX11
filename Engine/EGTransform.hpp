#pragma once
#include "EGComponent.hpp"
#include <SimpleMath.h>

#include "SimpleMath.h"

namespace Engine::Component
{
	class Transform : public Abstract::Component
	{
	public:
		Transform(const Abstract::GameObject* owner);
		~Transform() override = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void SetConstantBuffer();

		void SetPosition(DirectX::SimpleMath::Vector3 position) { m_position_ = position; }
		void SetRotation(DirectX::SimpleMath::Vector3 euler) { m_rotation_ = euler; }
		void SetRotation(DirectX::SimpleMath::Quaternion quaternion) { m_rotation_ = quaternion.ToEuler(); }
		void SetScale(DirectX::SimpleMath::Vector3 scale) { m_scale_ = scale; }

		void SetPosition(float x, float y, float z) { m_position_ = DirectX::SimpleMath::Vector3(x, y, z); }
		void SetRotation(float yaw, float pitch, float roll)
		{
			const DirectX::SimpleMath::Quaternion quaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				yaw, pitch, roll);
			m_rotation_ = quaternion.ToEuler();
		}
		void SetScale(float x, float y, float z) { m_scale_ = DirectX::SimpleMath::Vector3(x, y, z); }

		DirectX::SimpleMath::Vector3 GetPosition() const { return m_position_; }
		DirectX::SimpleMath::Vector3 GetRotation() const { return m_rotation_; }
		DirectX::SimpleMath::Vector3 GetScale() const { return m_scale_; }

	private:
		DirectX::SimpleMath::Vector3 m_position_{};
		DirectX::SimpleMath::Vector3 m_rotation_{};
		DirectX::SimpleMath::Vector3 m_scale_{1.0f, 1.0f, 1.0f};
	};
}
