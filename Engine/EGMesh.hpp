#pragma once
#include "EGRenderer.h"
#include "EGResource.hpp"

namespace Engine::Abstract
{
	class Mesh : public Resource
	{
	public:
		Mesh(
			const std::wstring& name, const std::wstring& key, const std::filesystem::path& path, 
			const Renderer::Vertex* vertex_data,
			const size_t* vertex_size,
			const UINT* index_data,
			const size_t* index_size);
		~Mesh() override = default;

		void Load() override;

		void CreateVertexBuffer(void* data, UINT Count);
		void CreateIndexBuffer(void* data, UINT Count);
		void BindBuffer();
		void Render();

	private:
		ComPtr<ID3D11Buffer> mVertexBuffer{};
		D3D11_BUFFER_DESC mVBDesc{};
		const Renderer::Vertex* mVertexData;
		const size_t* mVertexCount;

		ComPtr<ID3D11Buffer> mIndexBuffer{};
		D3D11_BUFFER_DESC mIBDesc{};
		const UINT* mIndexData;
		const size_t* mIndexCount;
	};
}
