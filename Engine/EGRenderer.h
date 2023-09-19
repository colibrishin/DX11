#pragma once
#include <memory>
#include "EGConstantBuffer.hpp"

namespace Engine::Renderer
{
	struct TransformBuffer
	{
		// TODO: Without padding version.
		DirectX::SimpleMath::Vector3 position;
		float _paddingA = 1.f;
		DirectX::SimpleMath::Vector3 rotation;
		float _paddingB = 1.f;
		DirectX::SimpleMath::Vector3 scale;
		float _paddingC = 1.f;
	};

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
