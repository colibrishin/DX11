#include "pch.h"
#include <fstream>
#include "EGTexture2D.hpp"

#include "EGD3DDevice.hpp"

namespace Engine::Graphics
{
	void Texture2D::Initialize()
	{
		load_tga_32bit();
		initialize_texture();
	}

	ID3D11ShaderResourceView** Texture2D::GetTexture()
	{
		return m_texture_view_.GetAddressOf();
	}

	Texture2D::Texture2D(
		const std::wstring& name, const std::wstring& key, 
		const std::filesystem::path& tga) : Resource(name, key, tga), m_tex_metadata_({})
	{
	}

	void Texture2D::Load()
	{
		Initialize();
	}

	void Texture2D::load_tga_32bit()
	{
		std::filesystem::path path = std::filesystem::current_path().parent_path() / GetPath();
		m_image_ = std::make_unique<DirectX::ScratchImage>();
		LoadFromTGAFile(path.c_str(), DirectX::TGA_FLAGS_NONE, &m_tex_metadata_, *m_image_);
	}

	void Texture2D::initialize_texture()
	{
		D3D11_TEXTURE2D_DESC texture_desc;
		D3D11_SHADER_RESOURCE_VIEW_DESC resource_desc;

		texture_desc.Height = m_tex_metadata_.height;
		texture_desc.Width = m_tex_metadata_.width;
		texture_desc.MipLevels = 0;
		texture_desc.ArraySize = 1;
		texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texture_desc.SampleDesc.Count = 1;
		texture_desc.SampleDesc.Quality = 0;
		texture_desc.Usage = D3D11_USAGE_DEFAULT;
		texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		texture_desc.CPUAccessFlags = 0;
		texture_desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

		const auto dev = D3DDevice::GetDevice();

		dev->CreateTexture(texture_desc, m_texture_.GetAddressOf());

		const unsigned int stride = (m_tex_metadata_.width * 4) * sizeof(unsigned char);
		const auto* image = m_image_->GetImage(0, 0, 0);
		dev->UpdateSubresource(m_texture_.Get(), image->pixels, stride, 0);

		resource_desc.Format = texture_desc.Format;
		resource_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		resource_desc.Texture2D.MostDetailedMip = 0;
		resource_desc.Texture2D.MipLevels = -1;

		// Create the shader resource view for the texture.
		dev->CreateShaderResourceView(
				m_texture_.Get(), resource_desc, m_texture_view_.GetAddressOf());

		// Generate mipmaps for this texture.
		dev->GenerateMips(m_texture_view_.Get());
	}
}
