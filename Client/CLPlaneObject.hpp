#pragma once
#include "../Engine/EGGameObject.hpp"
#include "../Engine/EGTransform.hpp"
#include "../Engine/EGCommon.hpp"
#include "../Engine/EGRigidBody.hpp"

namespace Client::Object
{
	class PlaneObject : public Engine::Abstract::RigidBody
	{
	public:
		PlaneObject(const std::wstring& name);
		~PlaneObject() override = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	protected:
		DirectX::SimpleMath::Vector3 m_offset_;
	};
}
