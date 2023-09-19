#pragma once
#include "pch.h"

#include "EGShader.hpp"
#include "EGTexture2D.hpp"

namespace Engine::Shader
{
	using namespace Microsoft::WRL;

	class TexturePixelShader final : public Abstract::Shader
	{
	public:
		TexturePixelShader(const std::wstring& key);
		~TexturePixelShader() override = default;

		void Load() override;
		void Update() override;
		void SetTexture(const std::weak_ptr<Graphics::Texture2D>& texture);

	private:
		ComPtr<ID3D11SamplerState> m_sampler_state_;
	};
}
