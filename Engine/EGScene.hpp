#pragma once
#include "EGCamera.hpp"
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
		~Scene() override = default;

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		Layer* GetLayer(UINT index) { return &mLayers[index]; }
		void AddGameObject(const std::weak_ptr<GameObject>& gameObject, UINT layerIndex);
		void RemoveGameObject(const std::weak_ptr<GameObject>& gameObject, UINT layerIndex);

		void GetSceneCoordination(XMMATRIX& view, XMMATRIX& projection) const;

	protected:
		std::weak_ptr<Object::Camera> m_camera_;

	private:
		Layer mLayers[Enums::LAYER::MAX];

		XMMATRIX m_world_{};
		XMMATRIX m_ortho_{};
		XMMATRIX m_projection_{};
	};
}
