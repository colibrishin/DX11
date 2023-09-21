#pragma once
#include "EGCamera.hpp"
#include "EGRenderer.h"
#include "EGComponent.hpp"
#include "EGEntity.hpp"
#include "EGLayer.hpp"

namespace Engine::Abstract
{
	using namespace DirectX;

	class Scene : public Entity
	{
	public:
		Scene(const std::wstring& name);
		virtual ~Scene() = default;

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		
		virtual void Render();

		Layer* GetLayer(UINT index) { return &mLayers[index]; }
		void AddGameObject(const std::weak_ptr<GameObject>& gameObject, UINT layerIndex);
		void RemoveGameObject(const std::weak_ptr<GameObject>& gameObject, UINT layerIndex);

	private:
		void Transpose(Renderer::PerspectiveMatrix& perspective_matrix);
		void UpdateBuffer(Renderer::PerspectiveMatrix& buffer) const;

		Layer mLayers[Enums::LAYER::MAX];
		std::weak_ptr<Object::Camera> m_camera_;

		Renderer::PerspectiveMatrix m_matrix_buffer_{};
		XMMATRIX m_world_{};
		XMMATRIX m_ortho_{};
		XMMATRIX m_projection_{};
	};
}
