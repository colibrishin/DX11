#pragma once
#include "pch.h"

#include "EGShader.hpp"

namespace Engine::Shader
{
	class DefaultPixelShader final : public Abstract::Shader
	{
	public:
		DefaultPixelShader(const std::wstring& key);
		~DefaultPixelShader() override = default;
		inline void Load() override;
	};

	inline DefaultPixelShader::DefaultPixelShader(const std::wstring& key) :
		Shader(
			L"DefaultPixelShader", 
			key,
			"TrianglePS.hlsl",
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			nullptr,
			nullptr,
			Graphics::ShaderStage::PS,
			"PS_Test")
	{
	}

	inline void DefaultPixelShader::Load()
	{
		Shader::Load();
	}
}
