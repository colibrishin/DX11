#pragma once
#include "../Engine/EGGraphics.hpp"
#include <Model.h>
#include "pch.h"

#include "../Engine/EGMesh.hpp"


//https://www.cgtrader.com/free-3d-models/food/vegetable/stylized-burger-45d51d8c-5836-4252-8b16-8a2d446cb7a9


namespace Client::Mesh
{
	using namespace Microsoft::WRL;

	class TestBurgerMesh : public Engine::Abstract::Mesh
	{
	public:
		TestBurgerMesh(const std::wstring& key);
		TestBurgerMesh(const TestBurgerMesh&) = default;
		~TestBurgerMesh() override = default;

	protected:
		void SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx, const DirectX::CommonStates* state) override;
	};

	inline TestBurgerMesh::TestBurgerMesh(const std::wstring& key) : Engine::Abstract::Mesh(
		L"TestBurgerMesh", key, "burger.cmo")
	{
	}

	inline void TestBurgerMesh::SetParameter(ID3D11Device* device, ID3D11DeviceContext* ctx,
		const DirectX::CommonStates* state)
	{
		
	}
}
