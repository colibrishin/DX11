#include "pch.h"
#include "EGMeshRenderer.hpp"
#include "EGSceneManager.hpp"
#include "EGShader.hpp"
#include "EGTransform.hpp"

namespace Engine::Component
{
	MeshRenderer::MeshRenderer(const Abstract::GameObject* owner)
		: Component(L"MeshRenderer" + std::to_wstring(GetID()), Enums::COMPONENTTYPE::MESH, owner)
	{
	}

	void MeshRenderer::Initialize()
	{
	}

	void MeshRenderer::Update()
	{
	}

	void MeshRenderer::FixedUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		if (const auto tr = GetOwner()->GetComponent<Engine::Component::Transform>().lock())
		{
			XMMATRIX view{};
			XMMATRIX projection{};

			Manager::SceneManager::GetActiveScene().lock()->GetSceneCoordination(view, projection);

			XMMATRIX worldPos = SimpleMath::Matrix::CreateWorld(
				DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Forward, DirectX::SimpleMath::Vector3::Up);

			const auto rotMat = SimpleMath::Matrix::CreateFromQuaternion(tr->GetRotation());

			XMMATRIX translateMat = XMMatrixTranslationFromVector(tr->GetPosition());

			worldPos = XMMatrixMultiply(worldPos, rotMat);
			worldPos = XMMatrixMultiply(worldPos, translateMat);

			mMesh.lock()->Render(
				worldPos,
				view,
				projection);
		}
	}

	void MeshRenderer::GetBoundingBox(BoundingBox& box) const
	{
		mMesh.lock()->GetBoundingBox(box);
	}

	Enums::BOUNDINGTYPE MeshRenderer::GetBoundingType() const
	{
		return mMesh.lock()->GetBoundingType();
	}
}
