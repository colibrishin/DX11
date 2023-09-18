#pragma once
#include <memory>
#include "EGEntity.hpp"
#include "EGEnums.hpp"

namespace Engine::Abstract
{
	class GameObject;

	class Component : public Entity
	{
	public:
		friend GameObject;
		~Component() override = default;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;

		[[nodiscard]] std::weak_ptr<GameObject> GetOwner() const { return mOwner; }
		[[nodiscard]] UINT GetUpdateOrder() const { return static_cast<UINT>(mType); }

	protected:
		Component(std::wstring name, Enums::COMPONENTTYPE type);

	private:
		const Enums::COMPONENTTYPE mType;
		std::weak_ptr<GameObject> mOwner;
	};

	inline Component::Component(std::wstring name, Enums::COMPONENTTYPE type) : Entity(std::move(name)), mType(type),
		mOwner({})
	{
	}
}
