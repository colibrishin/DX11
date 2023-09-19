#pragma once
#include <map>

#include "EGComponent.hpp"
#include "EGMesh.hpp"
#include "EGTexture2D.hpp"
#include "EGShader.hpp"
#include "EGTransform.hpp"
#include "EGTexturePS.hpp"
#include "EGGameObject.hpp"

namespace Engine
{
	template <typename T>
	class MeshRenderer : public Abstract::Component
	{
	public:
		MeshRenderer();
		~MeshRenderer() override = default;
		
		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void SetMesh(const std::weak_ptr<Abstract::Mesh<T>>& mesh) { mMesh = mesh; }
		void SetShader(const std::weak_ptr<Abstract::Shader>& shader) { mShaders[shader.lock()->GetStage()] = shader; }
		void SetTexture(const std::weak_ptr<Graphics::Texture2D>& texture) { mTexture = texture; }

	private:
		std::weak_ptr<Abstract::Mesh<T>> mMesh{};
		std::weak_ptr<Graphics::Texture2D> mTexture{};
		std::map<Graphics::ShaderStage, std::weak_ptr<Abstract::Shader>> mShaders{};
	};

	template <typename T>
	MeshRenderer<T>::MeshRenderer()
		: Component(L"MeshRenderer" + std::to_wstring(GetID()), Enums::COMPONENTTYPE::MESH)
	{
	}

	template <typename T>
	void MeshRenderer<T>::Initialize()
	{
	}

	template <typename T>
	void MeshRenderer<T>::Update()
	{
	}

	template <typename T>
	void MeshRenderer<T>::FixedUpdate()
	{
	}

	template <typename T>
	void MeshRenderer<T>::Render()
	{
		if(const auto tr = GetOwner().lock()->GetComponent<Abstract::Transform>().lock())
		{
			tr->SetConstantBuffer();
			bool texture = false;

			if(mTexture.lock())
			{
				texture = true;
			}

			for(const auto shader : mShaders)
			{
				if(const auto texturePS = std::dynamic_pointer_cast<Shader::TexturePixelShader>(shader.second.lock()))
				{
					if(texture) texturePS->SetTexture(mTexture);
				}
				shader.second.lock()->Update();
			}
			mMesh.lock()->Render();
		}
	}
}
