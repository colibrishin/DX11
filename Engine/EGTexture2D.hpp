#pragma once
#include <filesystem>
#include <wrl/client.h>

#include "EGResource.hpp"

namespace Engine::Graphics
{
	using namespace Microsoft::WRL;

	class Texture2D : public Abstract::Resource
	{
		struct TargaHeader
		{
		    unsigned char data1[12];
		    unsigned short width;
		    unsigned short height;
		    unsigned char bpp;
		    unsigned char data2;
		};

	public:
		explicit Texture2D(
			const std::wstring& name, const std::wstring& key, 
			const std::filesystem::path& tga);
		Texture2D(const Texture2D&) = default;
		~Texture2D() override = default;

		void Initialize();
		void Load() override;

		[[nodiscard]] ID3D11ShaderResourceView** GetTexture();

	private:
		char* load_tga_32bit();
		void initialize_texture(const char* data);

		ComPtr<ID3D11ShaderResourceView> m_texture_view_;
		ComPtr<ID3D11Texture2D> m_texture_;
		TargaHeader m_targa_header_;
	};
}
