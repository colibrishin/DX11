#pragma once
#include <map>

#include "EGComponent.hpp"
#include "EGMesh.hpp"

namespace Engine
{
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
		void SetShader(const std::weak_ptr<Abstract::Shader>& shader) { mShaders[shader.lock()->GetStage()] = shader; }

	private:
		std::weak_ptr<Abstract::Mesh> mMesh{};
		std::map<Graphics::ShaderStage, std::weak_ptr<Abstract::Shader>> mShaders{};
	};
}
