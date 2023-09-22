#pragma once
#include "EGGameObject.hpp"
#include "EGRenderer.h"

namespace Engine::Object
{
	class Light : public Abstract::GameObject
	{
	public:
		Light(const std::wstring& name);
		Light(const Light& other) = default;
		~Light() override = default;

		// in order of r, g, b, a
		void SetDiffuseColor(DirectX::XMFLOAT4 color);
		void SetDirection(DirectX::XMFLOAT3 dir);

		[[nodiscard]] DirectX::XMFLOAT4 GetDiffuseColor() const;
		[[nodiscard]] DirectX::XMFLOAT3 GetDirection() const;

		[[nodiscard]] Engine::Renderer::LightBuffer& GetLightBuffer();

	private:
		Renderer::LightBuffer m_lightBuffer_;
	};
}
