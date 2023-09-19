#include "pch.h"
#include "EGRenderer.h"

namespace Engine::Renderer
{
	std::shared_ptr<Graphics::ConstantBuffer> constantBuffers[(UINT)Graphics::CBTYPES::END]{};

	void Initialize()
	{
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
