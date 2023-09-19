#pragma once
#include "CLStoneTexture.hpp"
#include "../Engine/EGGameObject.hpp"
#include "../Engine/EGTransform.hpp"
#include "../Engine/EGTextureTriangleMesh.hpp"
#include "../Engine/EGCommon.hpp"

namespace Client::Object
{
	class TestObject : public Engine::Abstract::GameObject
	{
	public:
		TestObject(const std::wstring& name);
		~TestObject() override = default;
		inline void Initialize() override;
		inline void Update() override;
		inline void FixedUpdate() override;
		inline void Render() override;

		void move_up();
		void move_down();
		void move_left();
		void move_right();

		void scale_up();
		void scale_down();

		void shoot();

	protected:
		DirectX::SimpleMath::Vector3 m_offset_;
	};
}
