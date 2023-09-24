#include "pch.h"
#include "EGEntity.hpp"

namespace Engine::Abstract
{
	Entity::Entity(const std::wstring& name) : mName(name), mID(GetIDFromPointer(this))
	{
	}

	Entity::Entity(const Entity& other) : mName(other.mName), mID(GetIDFromPointer(this))
	{
	}
}
