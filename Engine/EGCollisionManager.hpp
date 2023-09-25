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
		static std::vector<std::weak_ptr<Abstract::RigidBody>> GetCollided(const std::weak_ptr<Abstract::GameObject>& weak);
		static void CheckGravityCollision(const std::weak_ptr<Abstract::RigidBody>& weak);

	private:
		static std::shared_ptr<Abstract::RigidBody> CheckCollisionality(const std::weak_ptr<Abstract::GameObject>& weak);
		static void ReleaseBoundingBox(void* bb2, const std::shared_ptr<Abstract::RigidBody>& shared);
		static void CompareLayerObjects(const Abstract::Layer* layer, const std::shared_ptr<Abstract::RigidBody>& rb);

		template <typename BoundingA, typename BoundingB>
		static Enums::COLLISIONCODE CheckCollision(const UINT rb, BoundingA& bb1, BoundingB& bb2, const UINT other_rb);

		static void SendEventByCollisionCode(const std::shared_ptr<Abstract::RigidBody>& rb,
		                                     const std::shared_ptr<Abstract::RigidBody>& other_rb,
		                                     Enums::COLLISIONCODE collisionCode);

		static void GetBounding(const std::shared_ptr<Abstract::RigidBody>& rb, void* box);
		static void CheckBoxSphereCasting(const std::shared_ptr<Abstract::RigidBody>& rb, void* bb1,
		                                  const std::shared_ptr<Abstract::RigidBody>& other_rb, void* bb2,
		                                  Enums::COLLISIONCODE& collisionCode);
		static void* InitializeBoundingBox(const std::shared_ptr<Abstract::RigidBody>& rb);
		static void SetBoundingCenter(const std::shared_ptr<Abstract::RigidBody>& rb, void* get, DirectX::SimpleMath::Vector3 center);


		inline static std::bitset<Enums::LAYER::MAX> m_collision_table_[Enums::LAYER::MAX];
		inline static std::map<UINT, std::set<UINT>> m_collided_;
	};

	template <typename BoundingA, typename BoundingB>
	Enums::COLLISIONCODE CollisionManager::CheckCollision(const UINT rb, BoundingA& bb1, BoundingB& bb2, const UINT other_rb)
	{
		if (m_collided_[rb].contains(other_rb) &&
			m_collided_[other_rb].contains(rb))
		{
			if (!bb1.Intersects(bb2))
			{
				m_collided_[rb].erase(other_rb);
				m_collided_[other_rb].erase(rb);

				return Enums::COLLISIONCODE_END;
			}
			else if (bb1.Intersects(bb2))
			{
				return Enums::COLLISIONCODE_STAY;
			}
		}
		else if (bb1.Intersects(bb2))
		{
			m_collided_[rb].insert(other_rb);
			m_collided_[other_rb].insert(rb);

			return Enums::COLLISIONCODE_START;
		}

		return Enums::COLLISIONCODE_NONE;
	}
}
