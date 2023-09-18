#include "pch.h"
#include "EGMesh.hpp"
#include <fstream>

#include <d3d11.h>

#include "EGD3DDevice.hpp"
#include "EGRenderer.h"

Engine::Abstract::Mesh::Mesh(std::wstring name, std::wstring key, std::filesystem::path path, 
			const Renderer::Vertex* vertex_data,
			const size_t* vertex_size,
			const UINT* index_data,
			const size_t* index_size) :
	Resource(std::move(name), std::move(key), std::move(path)), mVertexData(vertex_data), mVertexCount(vertex_size),
	mIndexData(index_data), mIndexCount(index_size)
{
	Mesh::Load();
}

void Engine::Abstract::Mesh::Load()
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

void Engine::Abstract::Mesh::CreateVertexBuffer(void* data, UINT Count)
{
	mVBDesc.ByteWidth = sizeof(Renderer::Vertex) * Count;
	mVBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	mVBDesc.Usage = D3D11_USAGE_DEFAULT;
	mVBDesc.CPUAccessFlags = 0;

	const D3D11_SUBRESOURCE_DATA subData{data, sizeof(Renderer::Vertex)};

	Graphics::D3DDevice::GetDevice()->CreateBuffer(mVBDesc, &subData, mVertexBuffer.GetAddressOf());
}

void Engine::Abstract::Mesh::CreateIndexBuffer(void* data, UINT Count)
{
	mIBDesc.ByteWidth = sizeof(UINT) * Count;
	mIBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	mIBDesc.Usage = D3D11_USAGE_DEFAULT;
	mIBDesc.CPUAccessFlags = 0;

	const D3D11_SUBRESOURCE_DATA subData{data};

	Graphics::D3DDevice::GetDevice()->CreateBuffer(mIBDesc, &subData, mIndexBuffer.GetAddressOf());
}

void Engine::Abstract::Mesh::BindBuffer()
{
	const UINT stride = sizeof(Renderer::Vertex);
	const UINT offset = 0;

	Graphics::D3DDevice::GetDevice()->BindVertexBuffer(0, 1, mVertexBuffer.GetAddressOf(), stride, offset);
	Graphics::D3DDevice::GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void Engine::Abstract::Mesh::Render()
{
	CreateVertexBuffer((void*)mVertexData, *mVertexCount);
	CreateIndexBuffer((void*)mIndexData, *mIndexCount);
	BindBuffer();
	Graphics::D3DDevice::GetDevice()->DrawIndexed(*mIndexCount, 0, 0);
	mVertexBuffer->Release();
	mIndexBuffer->Release();
}
