#include "pch.h"
#include "EGRenderer.h"

namespace Engine::Renderer
{
	std::shared_ptr<Graphics::ConstantBuffer> constantBuffers[(UINT)Graphics::CBTYPES::END]{};

	void Initialize()
	{
		constantBuffers[(UINT)Graphics::CBTYPES::TRANSFORM] = std::make_shared<Graphics::ConstantBuffer>();
		constantBuffers[(UINT)Graphics::CBTYPES::TRANSFORM]->Create(sizeof(TransformBuffer));
	}

	void Release()
	{
		for(const auto& buffer : constantBuffers)
		{
			buffer->Release();
		}
	}
}
