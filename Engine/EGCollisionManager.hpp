#pragma once
#include <bitset>

#include "EGEnums.hpp"

namespace Engine::Abstract
{
	class Layer;
	class GameObject;
	class RigidBody;
}

namespace Engine::Manager
{
	class CollisionManager
	{
	public:
		CollisionManager() = delete;
		CollisionManager(const CollisionManager&) = default;
		~CollisionManager() = default;

		static void Initialize();
		static void Update();
		static void SetCollision(const Enums::LAYER& layer1, const Enums::LAYER& layer2);
		static void UnsetCollision(const Enums::LAYER& layer1, const Enums::LAYER& layer2);

	private:
		static std::shared_ptr<Abstract::RigidBody> CheckCollisionality(const std::weak_ptr<Abstract::GameObject>& weak);
		static void CompareLayerObjects(const Abstract::Layer* layer, const std::shared_ptr<Abstract::RigidBody>& rb);

		inline static std::bitset<Enums::LAYER::MAX> m_collision_table_[Enums::LAYER::MAX];
		inline static std::map<UINT, std::set<UINT>> m_collided_;
	};
}
