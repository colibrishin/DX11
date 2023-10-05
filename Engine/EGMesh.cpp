#include "pch.h"
#include "EGMesh.hpp"

namespace Engine::Abstract 
{
	Mesh::Mesh(Enums::BOUNDINGTYPE type, const std::wstring& name, const std::wstring& key,
		const std::filesystem::path& path) : Resource(name, key, path), m_bounding_type_(type)
	{
		m_effect_factory_ = Graphics::D3DDevice::GetDevice()->CreateEffectFactory();
	}

	void Mesh::Load()
	{
		if (GetPath().empty())
		{
			return;
		}

		m_model_ = Graphics::D3DDevice::GetDevice()->LoadModelFromCMO(GetPath(), m_effect_factory_.get());
	}

	void Mesh::Render(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj)
	{
		Graphics::D3DDevice::GetDevice()->Draw(
			m_model_.get(),
			world,
			view,
			proj,
			[&](ID3D11Device* device, ID3D11DeviceContext* ctx, const DirectX::CommonStates* state)
			{
				SetParameter(device, ctx, state);
			});
	}

	void Mesh::GetBoundingBox(BoundingBox& box) const
	{
		for (const auto& mesh : m_model_->meshes)
		{
			BoundingBox::CreateMerged(box, box, mesh->boundingBox);
		}
	}

	Enums::BOUNDINGTYPE Mesh::GetBoundingType() const
	{
		return m_bounding_type_;
	}
}