#pragma once
#include "../Engine/EGGameObject.hpp"
#include "../Engine/EGTransform.hpp"
#include "../Engine/EGCommon.hpp"

namespace Client::Object
{
	class ExampleCupObject : public Engine::Abstract::GameObject
	{
	public:
		ExampleCupObject(const std::wstring& name);
		~ExampleCupObject() override = default;
		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void move_up();
		void move_down();
		void move_left();
		void move_right();

	protected:
		DirectX::SimpleMath::Vector3 m_offset_;
	};
}
