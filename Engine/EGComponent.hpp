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
		~Component() override = default;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;

		[[nodiscard]] const GameObject* GetOwner() const { return mOwner; }
		[[nodiscard]] UINT GetUpdateOrder() const { return static_cast<UINT>(mType); }

	protected:
		Component(const std::wstring& name, Enums::COMPONENTTYPE type, const Abstract::GameObject* owner);

	private:
		const Enums::COMPONENTTYPE mType;
		const Abstract::GameObject* mOwner;
	};

	inline Component::Component(const std::wstring& name, Enums::COMPONENTTYPE type, const Abstract::GameObject* owner) : Entity(name), mType(type), mOwner(owner)
	{
	}
}
