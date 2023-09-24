#include "pch.h"
#include "EGCollisionManager.hpp"
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

	void CollisionManager::CompareLayerObjects(const Abstract::Layer* layer, const std::shared_ptr<Abstract::RigidBody>& rb)
	{
		DirectX::BoundingBox bb1;
		DirectX::BoundingBox bb2;

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

				if(rb->m_bCollided_)
				{
					if(!bb1.Intersects(bb2))
					{
						m_collided_[rb->GetID()].erase(other_rb->GetID());
						m_collided_[other_rb->GetID()].erase(rb->GetID());

						rb->m_bCollided_ = m_collided_[rb->GetID()].size() > 0;
						other_rb->m_bCollided_ = m_collided_[other_rb->GetID()].size() > 0;

						rb->OnCollisionExit();
						other_rb->OnCollisionExit();
					}
				}
				else if (bb1.Intersects(bb2))
				{
					if(const bool collided_by_other = m_collided_[other_rb->GetID()].contains(rb->GetID()))
					{
						continue;
					}

					m_collided_[rb->GetID()].insert(other_rb->GetID());
					m_collided_[other_rb->GetID()].insert(rb->GetID());

					rb->m_bCollided_ = true;
					other_rb->m_bCollided_ = true;

					rb->OnCollision(other_rb.get());
					other_rb->OnCollision(rb.get());
				}
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
}
