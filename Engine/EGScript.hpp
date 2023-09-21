#pragma once
#include "EGComponent.hpp"

namespace Engine::Component
{
	class Script : public Abstract::Component
	{
	public:
		Script(const std::wstring& name) : Component(name, Enums::SCRIPT) {}
		Script(const Script&) = default;
		virtual ~Script() override = default;
	};
}
