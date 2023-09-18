#pragma once
#include <string>
#include <memory>

namespace Engine::Abstract
{
	class Entity : public std::enable_shared_from_this<Entity>
	{
	public:
		const std::wstring& GetName() const { return mName; }
		UINT32 GetID() const { return mID; }
		virtual ~Entity() = default;

		std::shared_ptr<Entity> GetPtr()
		{
			return shared_from_this();
		}

	protected:
		explicit Entity(std::wstring name) : mName(std::move(name)), mID(reinterpret_cast<UINT32>(this))
		{
		}

		Entity(const Entity& other) : mName(other.mName), mID(reinterpret_cast<UINT32>(this))
		{
		}

		void SetName(const std::wstring& name) { mName = name; }

	private:
		std::wstring mName{};
		const UINT32 mID{};
	};
}
