#pragma once
#include "EGComponent.hpp"

namespace Engine::Component
{
	class Script : public Abstract::Component
	{
	public:
		Script(
			const std::wstring& name, 
			const Abstract::GameObject* owner) :
		Component(name, Enums::SCRIPT, owner) {}
		Script(const Script&) = default;
		virtual ~Script() override = default;
	};
}
