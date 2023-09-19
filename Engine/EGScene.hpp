#pragma once
#include "EGComponent.hpp"
#include "EGEntity.hpp"
#include "EGLayer.hpp"

namespace Engine::Abstract
{
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
		Layer mLayers[Enums::LAYER::MAX];
	};

	inline Scene::Scene(const std::wstring& name) : Entity(name)
	{
	}

	inline void Scene::Initialize()
	{
		for(auto& ly : mLayers)
		{
			ly.Initialize();
		}
	}

	inline void Scene::Update()
	{
		for(auto& ly : mLayers)
		{
			ly.Update();
		}
	}

	inline void Scene::FixedUpdate()
	{
		for(auto& ly : mLayers)
		{
			ly.FixedUpdate();
		}
	}

	inline void Scene::Render()
	{
		for(auto& ly : mLayers)
		{
			ly.Render();
		}
	}

	inline void Scene::AddGameObject(const std::weak_ptr<GameObject>& gameObject, UINT layerIndex)
	{
		mLayers[layerIndex].AddGameObject(gameObject);
	}

	inline void Scene::RemoveGameObject(const std::weak_ptr<GameObject>& gameObject, UINT layerIndex)
	{
		mLayers[layerIndex].RemoveGameObject(gameObject);
	}
}
