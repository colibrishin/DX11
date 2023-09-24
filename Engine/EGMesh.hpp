#pragma once
#include <wrl/client.h>
#include "EGResource.hpp"
#include "EGD3DDevice.hpp"

namespace Engine::Abstract
{
	using namespace Microsoft::WRL;
	using namespace DirectX;

	class Mesh : public Resource
	{
	public:
		Mesh(const std::wstring& name, const std::wstring& key, const std::filesystem::path& path);
		~Mesh() override = default;

		void Load() override;
		virtual void Render(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj);
		virtual void GetBoundingBox(BoundingBox& box) const;

	protected:
		virtual void SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx, const DirectX::CommonStates* state) = 0;

	private:
		std::unique_ptr<IEffectFactory> m_effect_factory_;
		std::unique_ptr<Model> m_model_;
	};

	inline Mesh::Mesh(const std::wstring& name, const std::wstring& key, const std::filesystem::path& path): Resource(name, key, path)
	{
		m_effect_factory_ = Graphics::D3DDevice::GetDevice()->CreateEffectFactory();
	}

	inline void Mesh::Load()
	{
		if(GetPath().empty())
		{
			return;
		}

		m_model_ = Graphics::D3DDevice::GetDevice()->LoadModelFromCMO(GetPath(), m_effect_factory_.get());
	}

	inline void Mesh::Render(
		const XMMATRIX& world, 
		const XMMATRIX& view, 
		const XMMATRIX& proj)
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

	inline void Mesh::GetBoundingBox(BoundingBox& box) const
	{
		for(const auto& mesh : m_model_->meshes)
		{
			BoundingBox::CreateMerged(box, box, mesh->boundingBox);
		}
	}
}
