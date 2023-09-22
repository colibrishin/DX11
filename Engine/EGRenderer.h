#pragma once
#include <memory>
#include "EGConstantBuffer.hpp"

namespace Engine::Renderer
{
	struct PerspectiveMatrix
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

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

	struct LightBuffer
	{
		DirectX::XMFLOAT4 diffuseColor;
		DirectX::XMFLOAT3 lightDirection;
		float _padding;
	};

	// Shader input types

	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
	};

	struct TextureVertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 tex;
		DirectX::XMFLOAT3 normal;
	};

	extern std::shared_ptr<Graphics::ConstantBuffer> constantBuffers[];

	// Initialize the renderer
	void Initialize();
	void Release();
}
#pragma once
