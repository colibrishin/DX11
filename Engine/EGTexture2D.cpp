#include "pch.h"
#include <fstream>
#include "EGTexture2D.hpp"

#include "EGD3DDevice.hpp"

namespace Engine::Graphics
{
	void Texture2D::Initialize()
	{
		const auto* data = load_tga_32bit();
		initialize_texture(data);
	}

	ID3D11ShaderResourceView** Texture2D::GetTexture()
	{
		return m_texture_view_.GetAddressOf();
	}

	Texture2D::Texture2D(
		const std::wstring& name, const std::wstring& key, 
		const std::filesystem::path& tga) : Resource(name, key, tga), m_targa_header_({})
	{
	}

	void Texture2D::Load()
	{
		Initialize();
	}

	char* Texture2D::load_tga_32bit()
	{
		std::fstream file;
		std::filesystem::path path = std::filesystem::current_path().parent_path() / GetPath();

		file.open(path, std::ios::in | std::ios::binary);

		file.read(reinterpret_cast<char*>(&m_targa_header_), sizeof(m_targa_header_));

		const unsigned int stride = m_targa_header_.width * 4;
		const unsigned int data_size = m_targa_header_.height * stride;

		const auto from_file = new char[data_size];
		const auto ret = new char[data_size];
		file.read(from_file, data_size);

		// Initialize the index into the targa destination data array.
		unsigned int idx = 0;

		// Initialize the index into the targa image data.
		unsigned int k = data_size - stride;

		// Now copy the targa image data into the targa destination array in the correct order since the targa format is stored upside down and also is not in RGBA order.
		for(int y = 0; y < m_targa_header_.height; ++y)
		{
			for(int x = 0; x < m_targa_header_.width; ++x)
			{
				ret[idx + 0] = from_file[k + 2];  // Red.
				ret[idx + 1] = from_file[k + 1];  // Green.
				ret[idx + 2] = from_file[k + 0];  // Blue
				ret[idx + 3] = from_file[k + 3];  // Alpha

				// Increment the indexes into the targa data.
				k += 4;
				idx += 4;
			}

			// Set the targa image data index back to the preceding row at the beginning of the column since its reading it in upside down.
			k -= stride * 2;
		}

		// Release the targa image data now that it was copied into the destination array.
		delete [] from_file;

		return ret;
	}

	void Texture2D::initialize_texture(const char* data)
	{
		D3D11_TEXTURE2D_DESC texture_desc;
		D3D11_SHADER_RESOURCE_VIEW_DESC resource_desc;

		texture_desc.Height = m_targa_header_.width;
		texture_desc.Width = m_targa_header_.height;
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

		const unsigned int stride = (m_targa_header_.width * 4) * sizeof(unsigned char);
		dev->UpdateSubresource(m_texture_.Get(), (void*)data, stride, 0);

		resource_desc.Format = texture_desc.Format;
		resource_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		resource_desc.Texture2D.MostDetailedMip = 0;
		resource_desc.Texture2D.MipLevels = -1;

		// Create the shader resource view for the texture.
		dev->CreateShaderResourceView(
				m_texture_.Get(), resource_desc, m_texture_view_.GetAddressOf());

		// Generate mipmaps for this texture.
		dev->GenerateMips(m_texture_view_.Get());

		// Release the targa image data now that the image data has been loaded into the texture.
		delete[] data;
	}
}
