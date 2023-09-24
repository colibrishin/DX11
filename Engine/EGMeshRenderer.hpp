#pragma once
#include <map>

#include "EGCommon.hpp"
#include "EGComponent.hpp"
#include "EGMesh.hpp"
#include "EGShader.hpp"
#include "EGTransform.hpp"
#include "EGGameObject.hpp"

namespace Engine
{
	using namespace DirectX;

	class MeshRenderer : public Abstract::Component
	{
	public:
		MeshRenderer();
		~MeshRenderer() override = default;
		
		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void SetMesh(const std::weak_ptr<Abstract::Mesh>& mesh) { mMesh = mesh; }
		// SetShader
		// SetTexture

	private:
		std::weak_ptr<Abstract::Mesh> mMesh{};
	};

	inline MeshRenderer::MeshRenderer()
		: Component(L"MeshRenderer" + std::to_wstring(GetID()), Enums::COMPONENTTYPE::MESH)
	{
	}

	inline void MeshRenderer::Initialize()
	{
	}

	inline void MeshRenderer::Update()
	{
	}

	inline void MeshRenderer::FixedUpdate()
	{
	}

	inline void MeshRenderer::Render()
	{
		if(const auto tr = GetOwner().lock()->GetComponent<Abstract::Transform>().lock())
		{
			XMMATRIX view{};
			XMMATRIX projection{};

			Manager::SceneManager::GetActiveScene().lock()->GetSceneCoordination(view, projection);

			XMMATRIX worldPos = SimpleMath::Matrix::CreateWorld(
				tr->GetPosition(), DirectX::SimpleMath::Vector3::Forward, DirectX::SimpleMath::Vector3::Up);

			const auto rotMat = SimpleMath::Matrix::CreateFromYawPitchRoll(tr->GetRotation());
			worldPos = XMMatrixMultiply(worldPos, rotMat);

			mMesh.lock()->Render(
				worldPos,
				view, 
				projection);
		}
	}
}
