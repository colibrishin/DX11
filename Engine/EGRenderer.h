#pragma once
#include <memory>
#include "EGConstantBuffer.hpp"
#include "EGShader.hpp"
#include <SimpleMath.h>

namespace Engine
{
	namespace Abstract
	{
		class Mesh;
	}
}

namespace Engine::Renderer
{
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
	};

	extern std::weak_ptr<Abstract::Mesh> mesh;
	extern std::weak_ptr<Abstract::Shader> shader;
	extern std::shared_ptr<Graphics::ConstantBuffer> constantBuffers[];

	// Initialize the renderer
	void Initialize();
	void Release();
}
#pragma once
