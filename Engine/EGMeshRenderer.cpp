#include "pch.h"
#include "EGMeshRenderer.hpp"
#include "EGGameObject.hpp"

#include "EGTransform.hpp"

namespace Engine
{
	MeshRenderer::MeshRenderer()
		: Component(L"MeshRenderer" + std::to_wstring(GetID()), Enums::COMPONENTTYPE::MESH)
	{
	}

	void MeshRenderer::Initialize()
	{
	}

	void MeshRenderer::Update()
	{
	}

	void MeshRenderer::FixedUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		if(const auto tr = GetOwner().lock()->GetComponent<Abstract::Transform>().lock())
		{
			tr->SetConstantBuffer();

			for(const auto shader : mShaders)
			{
				shader.second.lock()->Update();
			}
			mMesh.lock()->Render();
		}
	}
}

