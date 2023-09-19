#pragma once
#include "pch.h"

#include "EGShader.hpp"

namespace Engine::Shader
{
	class TextureVertexShader final : public Abstract::Shader
	{
	public:
		TextureVertexShader(std::wstring key);
		~TextureVertexShader() override = default;
		inline void Load() override;

	private:
		const D3D11_INPUT_ELEMENT_DESC m_input_desc_[2] = 
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		const size_t m_input_size = std::size(m_input_desc_);
	};

	inline TextureVertexShader::TextureVertexShader(std::wstring key) :
		Shader(
			L"TextureVertexShader", 
			key,
			"TextureVS.hlsl",
			D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			m_input_desc_,
			&m_input_size,
			Graphics::ShaderStage::VS,
			"TextureVertexShader")
	{
	}

	inline void TextureVertexShader::Load()
	{
		Shader::Load();
	}
}
