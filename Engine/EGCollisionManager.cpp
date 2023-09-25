#include "pch.h"
#include "EGCollisionManager.hpp"

#include "EGGameObjectManager.hpp"
#include "EGLayer.hpp"

#include "EGRigidBody.hpp"
#include "EGSceneManager.hpp"

namespace Engine::Manager
{
	std::shared_ptr<Abstract::RigidBody> CollisionManager::CheckCollisionality(const std::weak_ptr<Abstract::GameObject>& weak)
	{
		if(const auto ptr = weak.lock())
		{
			if(auto rigidBody = std::dynamic_pointer_cast<Abstract::RigidBody>(ptr))
			{
				return rigidBody;
			}
		}

		return nullptr;
	}

	Enums::COLLISIONCODE CollisionManager::CheckCollision(const std::shared_ptr<Abstract::RigidBody>& rb,
	                                                      DirectX::BoundingOrientedBox& bb1, DirectX::BoundingOrientedBox& bb2,
	                                                      const std::shared_ptr<Abstract::RigidBody>& other_rb)
	{
		if(m_collided_[rb->GetID()].contains(other_rb->GetID()) && 
			m_collided_[other_rb->GetID()].contains(rb->GetID()))
		{
			if(!bb1.Intersects(bb2))
			{
				m_collided_[rb->GetID()].erase(other_rb->GetID());
				m_collided_[other_rb->GetID()].erase(rb->GetID());

				return Enums::COLLISIONCODE_END;
			}
			else if(bb1.Intersects(bb2))
			{
				return Enums::COLLISIONCODE_STAY;
			}
		}
		else if (bb1.Intersects(bb2))
		{
			m_collided_[rb->GetID()].insert(other_rb->GetID());
			m_collided_[other_rb->GetID()].insert(rb->GetID());

			return Enums::COLLISIONCODE_START;
		}

		return Enums::COLLISIONCODE_NONE;
	}

	void CollisionManager::SendEventByCollisionCode(const std::shared_ptr<Abstract::RigidBody>& rb, const std::shared_ptr<Abstract::RigidBody>& other_rb, const Enums::COLLISIONCODE collisionCode)
	{
		switch(collisionCode)
		{
		case Enums::COLLISIONCODE_START:
			rb->OnCollision(other_rb.get());
			other_rb->OnCollision(rb.get());
			break;
		case Enums::COLLISIONCODE_END:
			rb->OnCollisionExit(other_rb.get());
			other_rb->OnCollisionExit(rb.get());
			break;
		case Enums::COLLISIONCODE_COUNT:
		case Enums::COLLISIONCODE_STAY:
		case Enums::COLLISIONCODE_NONE:
		default: break;
		}
	}

	void CollisionManager::CompareLayerObjects(const Abstract::Layer* layer, const std::shared_ptr<Abstract::RigidBody>& rb)
	{
		DirectX::BoundingOrientedBox bb1;
		DirectX::BoundingOrientedBox bb2;

		for(const auto& obj : layer->mGameObjects)
		{
			if(const auto other_rb = CheckCollisionality(obj))
			{
				if(rb == other_rb)
				{
					continue;
				}

				rb->GetBoundingBox(bb1);
				other_rb->GetBoundingBox(bb2);

				const auto collisionCode = CheckCollision(rb, bb1, bb2, other_rb);
				SendEventByCollisionCode(rb, other_rb, collisionCode);
			}
		}
	}

	void CollisionManager::Initialize()
	{
		// Rigidbodys in the same layer can collided by default.
		for (size_t i = 0; i < (size_t)Enums::LAYER::MAX; ++i)
		{
			m_collision_table_[i].reset();
			m_collision_table_[i].set(i, true);
		}
	}

	void CollisionManager::Update()
	{
		if (const auto scene = SceneManager::GetActiveScene().lock())
		{
			for (size_t i = 0; i < (size_t)Enums::LAYER::MAX; ++i)
			{
				const auto current = scene->GetLayer((Enums::LAYER)i);

				for(const auto& obj : current->mGameObjects)
				{
					const auto rb = CheckCollisionality(obj);

					if(!rb)
					{
						continue;
					}

					CompareLayerObjects(current, rb);

					for (int j = 0; j < (size_t)Enums::LAYER::MAX; ++j)
					{
						if (i == j)
						{
							continue;
						}

						if (m_collision_table_[i].test(j))
						{
							CompareLayerObjects(scene->GetLayer(j), rb);
						}
					}

					if(rb->m_bGravity_override_)
					{
						Manager::CollisionManager::CheckGravityCollision(rb);
					}
				}
			}
		}
	}

	void CollisionManager::SetCollision(const Enums::LAYER& layer1, const Enums::LAYER& layer2)
	{
		m_collision_table_[(size_t)layer1].set((size_t)layer2, true);
		m_collision_table_[(size_t)layer2].set((size_t)layer1, true);
	}

	void CollisionManager::UnsetCollision(const Enums::LAYER& layer1, const Enums::LAYER& layer2)
	{
		m_collision_table_[(size_t)layer1].set((size_t)layer2, false);
		m_collision_table_[(size_t)layer2].set((size_t)layer1, false);
	}

	std::vector<std::weak_ptr<Abstract::RigidBody>> CollisionManager::GetCollided(
		const std::weak_ptr<Abstract::GameObject>& weak)
	{
		std::vector<std::weak_ptr<Abstract::RigidBody>> result;

		if(const auto rb = weak.lock())
		{
			const auto target = rb->GetID();
			const auto find_list = m_collided_.find(target);

			if(find_list != m_collided_.end())
			{
				for(const auto& id : find_list->second)
				{
					const std::weak_ptr<Abstract::RigidBody> other_rb = GameObjectManager::Find<Abstract::RigidBody>(id);

					if (other_rb.lock())
					{
						result.push_back(other_rb);
					}
				}
			}
		}

		return result;
	}

	void CollisionManager::CheckGravityCollision(const std::weak_ptr<Abstract::RigidBody>& weak)
	{
		const auto rb = weak.lock();
		auto nextTPos = rb->GetCenter() - DirectX::SimpleMath::Vector3{ 0, 1, 0 };

		DirectX::BoundingOrientedBox rb_nextBB;
		DirectX::BoundingOrientedBox other_nextBB;

		rb->GetBoundingBox(rb_nextBB);

		const auto collidedObj = Manager::CollisionManager::GetCollided(rb);

		if(collidedObj.empty())
		{
			rb->m_bGravity_ = true;
			rb->m_bGrounded_ = false;
			return;
		}

		for (const auto& ptr : collidedObj)
		{
			if(const auto other_rb = ptr.lock())
			{
				other_rb->GetBoundingBox(other_nextBB);

				const auto collisionCode = CheckCollision(rb, rb_nextBB, other_nextBB, other_rb);

				if(collisionCode == Enums::COLLISIONCODE_START || collisionCode == Enums::COLLISIONCODE_STAY)
				{
					rb->m_bGravity_ = false;
					rb->m_bGrounded_ = true;
				}
				else if(collisionCode == Enums::COLLISIONCODE_END || collisionCode == Enums::COLLISIONCODE_NONE)
				{
					rb->m_bGravity_ = true;
					rb->m_bGrounded_ = false;
				}
			}
		}
	}
}
