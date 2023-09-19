#pragma once
#include <memory>
#include "EGConstantBuffer.hpp"

namespace Engine::Renderer
{
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
	};

	struct TextureVertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 tex;
	};

	extern std::shared_ptr<Graphics::ConstantBuffer> constantBuffers[];

	// Initialize the renderer
	void Initialize();
	void Release();
}
#pragma once
