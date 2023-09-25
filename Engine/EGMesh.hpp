#pragma once
#include "EGResource.hpp"
#include "EGD3DDevice.hpp"
#include "EGEnums.hpp"

namespace Engine::Abstract
{
	using namespace DirectX;

	class Mesh : public Resource
	{
	public:
		Mesh(Enums::BOUNDINGTYPE type, const std::wstring& name, const std::wstring& key, const std::filesystem::path& path);

		~Mesh() override = default;
		void Load() override;

		virtual void Render(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj);
		virtual void GetBoundingBox(BoundingBox& box) const;
		Enums::BOUNDINGTYPE GetBoundingType() const;

	protected:
		virtual void SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx, const DirectX::CommonStates* state) = 0;

	private:
		std::unique_ptr<IEffectFactory> m_effect_factory_;
		std::unique_ptr<Model> m_model_;
		Enums::BOUNDINGTYPE m_bounding_type_;
	};
}
