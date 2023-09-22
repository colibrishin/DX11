#pragma once
#include "EGGameObject.hpp"

namespace Engine::Object
{
	class Light : public Abstract::GameObject
	{
	public:
		Light(const std::wstring& name);
		Light(const Light& other) = default;
		~Light() override = default;

		void SetDiffuseColor(DirectX::XMFLOAT4 color);
		void SetDirection(DirectX::XMFLOAT3 dir);

		[[nodiscard]] DirectX::XMFLOAT4 GetDiffuseColor() const;
		[[nodiscard]] DirectX::XMFLOAT3 GetDirection() const;

	private:
		DirectX::XMFLOAT4 m_diffuseColor_;
		DirectX::XMFLOAT3 m_direction_;
	};
}
