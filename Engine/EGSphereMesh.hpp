#pragma once
#include "pch.h"
#include "EGMesh.hpp"
#include <GeometricPrimitive.h>

namespace Engine::Mesh
{
	using namespace DirectX;

	class SphereMesh : public Abstract::Mesh
	{
	public:
		SphereMesh(const std::wstring& key, float diameter);
		SphereMesh(const SphereMesh& other) = default;
		~SphereMesh() override = default;

		void Render(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj) override;
		virtual void GetBoundingBox(BoundingBox& box) const override;

	protected:
		void SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx, const DirectX::CommonStates* state) override;

	private:
		std::unique_ptr<GeometricPrimitive> m_sphere_;
		float m_diameter_;
	};

	inline void SphereMesh::Render(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj)
	{
		m_sphere_->Draw(world, view, proj, Colors::White, nullptr, false, nullptr);
	}

	inline void SphereMesh::GetBoundingBox(BoundingBox& box) const
	{
		return BoundingBox::CreateFromSphere(box, BoundingSphere({}, m_diameter_ / 2));
	}

	inline void SphereMesh::SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx,
	                                     const DirectX::CommonStates* state)
	{
	}

	inline SphereMesh::SphereMesh(const std::wstring& key, float diameter) : Mesh(Enums::BOUNDINGTYPE_SPHERE, std::to_wstring(GetID()) + L" BoxMesh", key, "")
	{
		m_diameter_ = diameter;
		m_sphere_ = GetDevice()->CreateSphere(diameter);
	}
}
