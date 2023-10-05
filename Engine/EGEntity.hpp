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
		template<typename T>
		std::shared_ptr<T> GetPtr() { return std::static_pointer_cast<T>(shared_from_this()); }

	protected:
		explicit Entity(const std::wstring& name);
		Entity(const Entity& other);

		void SetName(const std::wstring& name) { mName = name; }

	private:
		std::wstring mName{};
		const UINT32 mID{};
	};
}
