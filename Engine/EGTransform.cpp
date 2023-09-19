#include "pch.h"
#include "EGTransform.hpp"

#include "EGConstantBuffer.hpp"
#include "EGRenderer.h"

namespace Engine::Abstract
{
	Transform::Transform()
		: Component(L"Transform" + std::to_wstring(GetID()), Enums::COMPONENTTYPE::TRANSFORM),
		m_buffer_({}, {}, {}, {}, {1.0f, 1.0f, 1.0f}, {})
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::FixedUpdate()
	{
	}

	void Transform::Render()
	{
	}

	void Transform::SetConstantBuffer()
	{
		const std::weak_ptr pb = Renderer::constantBuffers[(UINT)Graphics::CBTYPES::TRANSFORM];

		pb.lock()->Bind(&m_buffer_);
		pb.lock()->SetPipeline(Graphics::ShaderStage::VS);
	}

}
