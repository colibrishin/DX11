#pragma once
#include "../Engine/EGGraphics.hpp"
#include <Model.h>
#include "pch.h"

#include "../Engine/EGMesh.hpp"

namespace Client::Mesh
{
	using namespace Microsoft::WRL;

	class ExampleCupMesh : public Engine::Abstract::Mesh
	{
	public:
		ExampleCupMesh(const std::wstring& key);
		ExampleCupMesh(const ExampleCupMesh&) = default;
		~ExampleCupMesh() override = default;

	protected:
		void SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx, const DirectX::CommonStates* state) override;
	};

	inline ExampleCupMesh::ExampleCupMesh(const std::wstring& key) : Engine::Abstract::Mesh(
		L"ExampleCupMesh", key, "cup.cmo")
	{
	}

	inline void ExampleCupMesh::SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx,
		const DirectX::CommonStates* state)
	{
	}
}
