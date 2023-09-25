#pragma once
#include "pch.h"
#include "EGMesh.hpp"
#include <GeometricPrimitive.h>

namespace Engine::Mesh
{
	using namespace DirectX;

	class BoxMesh : public Abstract::Mesh
	{
	public:
		BoxMesh(const std::wstring& key, const SimpleMath::Vector3& size);
		BoxMesh(const BoxMesh& other) = default;
		~BoxMesh() override = default;

		void Render(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj) override;
		void GetBoundingBox(BoundingBox& box) const override;

	protected:
		void SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx, const DirectX::CommonStates* state) override;

	private:
		std::unique_ptr<GeometricPrimitive> m_box_;
		SimpleMath::Vector3 m_size_;
	};

	inline void BoxMesh::Render(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj)
	{
		m_box_->Draw(world, view, proj, Colors::White, nullptr, false, nullptr);
	}

	inline void BoxMesh::GetBoundingBox(BoundingBox& box) const
	{
		BoundingBox::CreateFromPoints(box, m_size_ / 2, -m_size_ / 2);
	}

	inline void BoxMesh::SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx,
		const DirectX::CommonStates* state)
	{
	}

	inline BoxMesh::BoxMesh(const std::wstring& key, const SimpleMath::Vector3& size) : Mesh(std::to_wstring(GetID()) + L" BoxMesh", key, "")
	{
		m_size_ = size;
		m_box_ = GetDevice()->CreateBox(m_size_);
	}
}
