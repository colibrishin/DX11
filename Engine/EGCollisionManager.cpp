#include "pch.h"
#include "EGCollisionManager.hpp"
#include <any>
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

	void CollisionManager::ReleaseBoundingBox(void* bb2, const std::shared_ptr<Abstract::RigidBody>& shared)
	{
		if(shared->GetBoundingType() == Enums::BOUNDINGTYPE_BOX)
			delete static_cast<DirectX::BoundingOrientedBox*>(bb2);
		else
			delete static_cast<DirectX::BoundingSphere*>(bb2);
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

	void CollisionManager::GetBounding(const std::shared_ptr<Abstract::RigidBody>& rb, void* box)
	{
		if(rb->GetBoundingType() == Enums::BOUNDINGTYPE_SPHERE)
			rb->GetBoundingSphere(*static_cast<DirectX::BoundingSphere*>(box));
		else
			rb->GetBoundingBox(*static_cast<DirectX::BoundingOrientedBox*>(box));
	}

	void CollisionManager::CheckBoxSphereCasting(const std::shared_ptr<Abstract::RigidBody>& rb, void* bb1, const std::shared_ptr<Abstract::RigidBody>& other_rb, void* bb2, Enums::COLLISIONCODE& collisionCode)
	{
		if(rb->GetBoundingType() == Enums::BOUNDINGTYPE_BOX && other_rb->GetBoundingType() == Enums::BOUNDINGTYPE_BOX)
		{
			collisionCode = CheckCollision(
				rb->GetID(),
				*static_cast<DirectX::BoundingOrientedBox*>(bb1),
				*static_cast<DirectX::BoundingOrientedBox*>(bb2),
				other_rb->GetID());
		}
		else if (rb->GetBoundingType() == Enums::BOUNDINGTYPE_SPHERE && other_rb->GetBoundingType() == Enums::BOUNDINGTYPE_SPHERE)
		{
			collisionCode = CheckCollision(
				rb->GetID(),
				*static_cast<DirectX::BoundingSphere*>(bb1),
				*static_cast<DirectX::BoundingSphere*>(bb2),
				other_rb->GetID());
		}
		else if (rb->GetBoundingType() == Enums::BOUNDINGTYPE_BOX && other_rb->GetBoundingType() == Enums::BOUNDINGTYPE_SPHERE)
		{
			collisionCode = CheckCollision(
				rb->GetID(),
				*static_cast<DirectX::BoundingOrientedBox*>(bb1),
				*static_cast<DirectX::BoundingSphere*>(bb2),
				other_rb->GetID());
		}
		else if (rb->GetBoundingType() == Enums::BOUNDINGTYPE_SPHERE && other_rb->GetBoundingType() == Enums::BOUNDINGTYPE_BOX)
		{
			collisionCode = CheckCollision(
				rb->GetID(),
				*static_cast<DirectX::BoundingSphere*>(bb1),
				*static_cast<DirectX::BoundingOrientedBox*>(bb2),
				other_rb->GetID());
		}
		else
		{
			collisionCode = Enums::COLLISIONCODE_NONE;
		}
	}

	void* CollisionManager::InitializeBoundingBox(const std::shared_ptr<Abstract::RigidBody>& rb)
	{
		void* bb1;

		if(rb->GetBoundingType() == Enums::BOUNDINGTYPE_BOX)
			bb1 = new DirectX::BoundingOrientedBox();
		else
			bb1 = new DirectX::BoundingSphere();

		return bb1;
	}

	void CollisionManager::SetBoundingCenter(const std::shared_ptr<Abstract::RigidBody>& rb, void* get, DirectX::SimpleMath::Vector3 center)
	{
		if(rb->GetBoundingType() == Enums::BOUNDINGTYPE_BOX)
			static_cast<DirectX::BoundingOrientedBox*>(get)->Center = center;
		else if(rb->GetBoundingType() == Enums::BOUNDINGTYPE_SPHERE)
			static_cast<DirectX::BoundingSphere*>(get)->Center = center;
	}

	void CollisionManager::CompareLayerObjects(const Abstract::Layer* layer, const std::shared_ptr<Abstract::RigidBody>& rb)
	{
		void* bb1 = InitializeBoundingBox(rb);

		for(const auto& obj : layer->mGameObjects)
		{
			if(const auto other_rb = CheckCollisionality(obj))
			{
				if(rb == other_rb)
				{
					continue;
				}

				void* bb2 = InitializeBoundingBox(other_rb);

				GetBounding(rb, bb1);
				GetBounding(other_rb, bb2);

				Enums::COLLISIONCODE collisionCode;
				CheckBoxSphereCasting(rb, bb1, other_rb, bb2, collisionCode);

				SendEventByCollisionCode(rb, other_rb, collisionCode);
				ReleaseBoundingBox(bb2, other_rb);
			}
		}

		ReleaseBoundingBox(bb1, rb);
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
		const auto nextTPos = rb->GetCenter() - DirectX::SimpleMath::Vector3{ 0, 1, 0 };

		void* rb_nextBB = InitializeBoundingBox(rb);
		GetBounding(rb, rb_nextBB);
		SetBoundingCenter(rb, rb_nextBB, nextTPos);

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
				void* other_BB = InitializeBoundingBox(other_rb);
				GetBounding(other_rb, other_BB);

				Enums::COLLISIONCODE collisionCode;

				CheckBoxSphereCasting(rb, rb_nextBB, other_rb, other_BB, collisionCode);

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

				ReleaseBoundingBox(other_BB, other_rb);
			}
		}

		ReleaseBoundingBox(rb_nextBB, rb);
	}
}
