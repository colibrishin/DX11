#include "pch.h"
#include "EGRenderer.h"

namespace Engine::Renderer
{
	std::weak_ptr<Abstract::Mesh> mesh{};
	std::weak_ptr<Abstract::Shader> shader{};
	std::shared_ptr<Graphics::ConstantBuffer> constantBuffers[(UINT)Graphics::CBTYPES::END]{};

	void Initialize()
	{
		mesh = {};
		shader = {};
		for(auto& buffer : constantBuffers)
		{
			buffer = std::make_shared<Graphics::ConstantBuffer>();
		}
	}

	void Release()
	{
		for(const auto& buffer : constantBuffers)
		{
			buffer->Release();
		}
	}
}
