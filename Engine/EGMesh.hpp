#pragma once
#include <wrl/client.h>
#include "EGRenderer.h"
#include "EGResource.hpp"

namespace Engine::Abstract
{
	using namespace Microsoft::WRL;
	template <typename T>
	class Mesh : public Resource
	{
	public:
		Mesh(
			const std::wstring& name, const std::wstring& key, const std::filesystem::path& path, 
			const T* vertex_data,
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
		const T* mVertexData;
		const size_t* mVertexCount;

		ComPtr<ID3D11Buffer> mIndexBuffer{};
		D3D11_BUFFER_DESC mIBDesc{};
		const UINT* mIndexData;
		const size_t* mIndexCount;
	};

	template <typename T>
	Mesh<T>::Mesh(const std::wstring& name, const std::wstring& key, const std::filesystem::path& path,
		const T* vertex_data, const size_t* vertex_size, const UINT* index_data, const size_t* index_size): Resource(name, key, path), mVertexData(vertex_data), mVertexCount(vertex_size), mIndexData(index_data), mIndexCount(index_size)
	{
	}

	template <typename T>
	void Mesh<T>::Load()
	{
		// TODO: Load mesh data from resource file.
		/*
			std::fstream file;

			file.open(path, std::ios::binary | std::ios::in);
			file.read(reinterpret_cast<char*>(mVertexCount), sizeof(UINT));
			mVertexData = new Renderer::Vertex[mVertexCount];
			file.read(reinterpret_cast<char*>(mVertexData), sizeof(Renderer::Vertex) * mVertexCount);
			file.read(reinterpret_cast<char*>(mIndexCount), sizeof(UINT));
			mIndexData = new UINT[mIndexCount];
			file.read(reinterpret_cast<char*>(mIndexData), sizeof(UINT) * mIndexCount);

			file.close();
			*/
	}

	template <typename T>
	void Mesh<T>::CreateVertexBuffer(void* data, UINT Count)
	{
		mVBDesc.ByteWidth = sizeof(T) * Count;
		mVBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		mVBDesc.Usage = D3D11_USAGE_DEFAULT;
		mVBDesc.CPUAccessFlags = 0;

		const D3D11_SUBRESOURCE_DATA subData{data};

		Graphics::D3DDevice::GetDevice()->CreateBuffer(mVBDesc, &subData, mVertexBuffer.GetAddressOf());
	}

	template <typename T>
	void Mesh<T>::CreateIndexBuffer(void* data, UINT Count)
	{
		mIBDesc.ByteWidth = sizeof(UINT) * Count;
		mIBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		mIBDesc.Usage = D3D11_USAGE_DEFAULT;
		mIBDesc.CPUAccessFlags = 0;

		const D3D11_SUBRESOURCE_DATA subData{data};

		Graphics::D3DDevice::GetDevice()->CreateBuffer(mIBDesc, &subData, mIndexBuffer.GetAddressOf());
	}

	template <typename T>
	void Mesh<T>::BindBuffer()
	{
		const UINT stride = sizeof(T);
		const UINT offset = 0;

		Graphics::D3DDevice::GetDevice()->BindVertexBuffer(0, 1, mVertexBuffer.GetAddressOf(), stride, offset);
		Graphics::D3DDevice::GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	template <typename T>
	void Mesh<T>::Render()
	{
		CreateVertexBuffer((void*)mVertexData, *mVertexCount);
		CreateIndexBuffer((void*)mIndexData, *mIndexCount);
		BindBuffer();
		Graphics::D3DDevice::GetDevice()->DrawIndexed(*mIndexCount, 0, 0);
		mVertexBuffer->Release();
		mIndexBuffer->Release();
	}
}
