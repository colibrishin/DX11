#pragma once
#include "EGComponent.hpp"
#include <SimpleMath.h>

namespace Engine::Abstract
{
	class Transform : public Component
	{
	public:
		struct TransformBuffer
		{
			// TODO: Without padding version.
			DirectX::SimpleMath::Vector3 position;
			float _paddingA = 1.f;
			DirectX::SimpleMath::Vector3 rotation;
			float _paddingB = 1.f;
			DirectX::SimpleMath::Vector3 scale;
			float _paddingC = 1.f;
		};

		Transform();
		~Transform() override = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void SetConstantBuffer();

		void SetPosition(DirectX::SimpleMath::Vector3 position) { m_buffer_.position = position; }
		void SetRotation(DirectX::SimpleMath::Vector3 rotation) { m_buffer_.rotation = rotation; }
		void SetScale(DirectX::SimpleMath::Vector3 scale) { m_buffer_.scale = scale; }

		void SetPosition(float x, float y, float z) { m_buffer_.position = DirectX::SimpleMath::Vector3(x,y,z); }
		void SetRotation(float x, float y, float z) { m_buffer_.rotation = DirectX::SimpleMath::Vector3(x, y, z); }
		void SetScale(float x, float y, float z) { m_buffer_.scale = DirectX::SimpleMath::Vector3(x, y, z); }

		DirectX::SimpleMath::Vector3 GetPosition() const { return m_buffer_.position; }
		DirectX::SimpleMath::Vector3 GetRotation() const { return m_buffer_.rotation; }
		DirectX::SimpleMath::Vector3 GetScale() const { return m_buffer_.scale; }

	private:
		TransformBuffer m_buffer_;
	};
}
