#pragma once
#include "pch.h"
#include "EGMesh.hpp"
#include <GeometricPrimitive.h>

#include "EGBoxMesh.hpp"

namespace Engine::Mesh
{
	using namespace DirectX;

	class PlaneMesh : public Mesh::BoxMesh
	{
	public:
		PlaneMesh(const std::wstring& key, const SimpleMath::Vector3& size);
		PlaneMesh(const PlaneMesh& other) = default;
		~PlaneMesh() override = default;

		void Render(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj) override;

	protected:
		void SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx, const DirectX::CommonStates* state) override;

	private:
		std::unique_ptr<GeometricPrimitive> m_plane_;
		SimpleMath::Vector3 m_size_;
	};

	inline void PlaneMesh::Render(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj)
	{
		m_plane_->Draw(world, view, proj, Colors::White, nullptr, false, nullptr);
	}

	inline void PlaneMesh::SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx,
	                                    const DirectX::CommonStates* state)
	{
	}

	inline PlaneMesh::PlaneMesh(const std::wstring& key, const SimpleMath::Vector3& size): BoxMesh(key, {size.x, 1.0f, size.z})
	{
		m_size_ = size;
		m_size_.y = 1.0f;
		m_plane_ = GetDevice()->CreateBox(m_size_);
	}
}
