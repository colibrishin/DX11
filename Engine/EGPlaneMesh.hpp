#pragma once
#include "EGMesh.hpp"
#include <GeometricPrimitive.h>

namespace Engine::Mesh
{
	using namespace DirectX;

	class PlaneMesh : public Abstract::Mesh
	{
	public:
		PlaneMesh(const std::wstring& key);
		PlaneMesh(const PlaneMesh& other) = default;
		~PlaneMesh() override = default;

		void Render(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj) override;

	protected:
		void SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx, const DirectX::CommonStates* state) override;

	private:
		std::unique_ptr<GeometricPrimitive> m_plane_;
	};

	inline void PlaneMesh::Render(const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj)
	{
		m_plane_->Draw(world, view, proj, Colors::White, nullptr, false, nullptr);
	}

	inline void PlaneMesh::SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx,
		const DirectX::CommonStates* state)
	{
	}

	inline PlaneMesh::PlaneMesh(const std::wstring& key): Mesh(std::to_wstring(GetID()) + L" PlaneMesh", key, "")
	{
		m_plane_ = GetDevice()->CreateBox({ 100.0f, 1.0f, 100.0f });
	}
}
