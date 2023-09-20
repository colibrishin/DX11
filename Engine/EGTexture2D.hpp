#pragma once
#include <filesystem>
#include <wrl/client.h>
#include <DirectXTex.h>

#include "EGResource.hpp"

namespace Engine::Graphics
{
	using namespace Microsoft::WRL;

	class Texture2D : public Abstract::Resource
	{
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
		void load_tga_32bit();
		void initialize_texture();

		ComPtr<ID3D11ShaderResourceView> m_texture_view_;
		ComPtr<ID3D11Texture2D> m_texture_;
		DirectX::TexMetadata m_tex_metadata_;
		std::unique_ptr<DirectX::ScratchImage> m_image_;
	};
}
