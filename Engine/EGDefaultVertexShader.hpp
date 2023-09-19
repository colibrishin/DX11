#pragma once
#include "pch.h"

#include "EGShader.hpp"

namespace Engine::Shader
{
	class DefaultVertexShader final : public Abstract::Shader
	{
	public:
		DefaultVertexShader(std::wstring key);
		~DefaultVertexShader() override = default;
		inline void Load() override;

	private:
		const D3D11_INPUT_ELEMENT_DESC m_input_desc_[2] = 
		{
			{
				"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA
			},
			{
				"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA
			},
		};

		const size_t m_input_size = std::size(m_input_desc_);
	};

	inline DefaultVertexShader::DefaultVertexShader(std::wstring key) :
		Shader(
			L"DefaultVertexShader", 
			key,
			"TriangleVS.hlsl",
			D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			m_input_desc_,
			&m_input_size,
			Graphics::ShaderStage::VS,
			"VS_Test")
	{
	}

	inline void DefaultVertexShader::Load()
	{
		Shader::Load();
	}
}
