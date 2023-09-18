#pragma once
#include "pch.h"

#include "EGShader.hpp"

namespace Engine::Shader
{
	class DefaultPixelShader final : public Abstract::Shader
	{
	public:
		DefaultPixelShader(std::wstring key);
		~DefaultPixelShader() override = default;
		inline void Load() override;
	};

	inline DefaultPixelShader::DefaultPixelShader(std::wstring key) :
		Shader(
			L"DefaultPixelShader", 
			std::move(key),
			"TrianglePS.hlsl",
			D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
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
