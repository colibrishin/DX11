#include "pch.h"
#include "EGTexturePS.hpp"

namespace Engine::Shader
{
	TexturePixelShader::TexturePixelShader(const std::wstring& key) :
		Shader(
			L"TexturePixelShader", 
			key,
			"TexturePS.hlsl",
			D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			nullptr,
			nullptr,
			Graphics::ShaderStage::PS,
			"TexturePixelShader")
	{
	}

	void TexturePixelShader::Load()
	{
		Shader::Load();

		D3D11_SAMPLER_DESC sampler_desc;

		sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.MipLODBias = 0.0f;
		sampler_desc.MaxAnisotropy = 1;
		sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampler_desc.BorderColor[0] = 0;
		sampler_desc.BorderColor[1] = 0;
		sampler_desc.BorderColor[2] = 0;
		sampler_desc.BorderColor[3] = 0;
		sampler_desc.MinLOD = 0;
		sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

		Graphics::D3DDevice::GetDevice()->CreateSampler(sampler_desc, m_sampler_state_.GetAddressOf());
	}

	void TexturePixelShader::Update()
	{
		Shader::Update();
		Graphics::D3DDevice::GetDevice()->BindSamplerState(m_sampler_state_.GetAddressOf());
	}

	void TexturePixelShader::SetTexture(const std::weak_ptr<Graphics::Texture2D>& texture)
	{
		Graphics::D3DDevice::GetDevice()->BindPixelShaderResource(texture.lock()->GetTexture());
	}
} 
