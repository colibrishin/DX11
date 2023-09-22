#include "pch.h"
#include "EGRenderer.h"

namespace Engine::Renderer
{
	std::shared_ptr<Graphics::ConstantBuffer> constantBuffers[(UINT)Graphics::CBTYPES::END]{};

	void Initialize()
	{
		constantBuffers[(UINT)Graphics::CBTYPES::LIGHT] = std::make_shared<Graphics::ConstantBuffer>(Graphics::CBTYPES::LIGHT);
		constantBuffers[(UINT)Graphics::CBTYPES::LIGHT]->Create(sizeof(LightBuffer));

		constantBuffers[(UINT)Graphics::CBTYPES::PERSPECTIVE] = std::make_shared<Graphics::ConstantBuffer>(Graphics::CBTYPES::PERSPECTIVE);
		constantBuffers[(UINT)Graphics::CBTYPES::PERSPECTIVE]->Create(sizeof(PerspectiveMatrix));

		constantBuffers[(UINT)Graphics::CBTYPES::TRANSFORM] = std::make_shared<Graphics::ConstantBuffer>(Graphics::CBTYPES::TRANSFORM);
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
