#pragma once
#include <map>

#include "EGCommon.hpp"
#include "EGComponent.hpp"
#include "EGMesh.hpp"

namespace Engine::Component
{
	using namespace DirectX;

	class MeshRenderer : public Abstract::Component
	{
	public:
		MeshRenderer(const Abstract::GameObject* owner);
		~MeshRenderer() override = default;
		
		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void SetMesh(const std::weak_ptr<Abstract::Mesh>& mesh)
		{
			mMesh = mesh;
		}
		// SetShader
		// SetTexture

		void GetBoundingBox(BoundingBox& box) const;
		Enums::BOUNDINGTYPE GetBoundingType() const;

	private:
		std::weak_ptr<Abstract::Mesh> mMesh{};
	};
}
