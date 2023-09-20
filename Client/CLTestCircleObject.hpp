#pragma once
#include "CLStoneTexture.hpp"
#include "../Engine/EGGameObject.hpp"
#include "../Engine/EGTransform.hpp"
#include "../Engine/EGTextureTriangleMesh.hpp"
#include "../Engine/EGCommon.hpp"

namespace Client::Object
{
	class TestCircleObject : public Engine::Abstract::GameObject
	{
	public:
		TestCircleObject(const std::wstring& name);
		~TestCircleObject() override = default;
		inline void Initialize() override;
		inline void Update() override;
		inline void FixedUpdate() override;
		inline void Render() override;

	protected:
		DirectX::SimpleMath::Vector3 m_offset_;
	};
}
