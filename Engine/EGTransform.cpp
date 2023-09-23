#include "pch.h"
#include "EGTransform.hpp"

namespace Engine::Abstract
{
	Transform::Transform()
		: Component(L"Transform" + std::to_wstring(GetID()), Enums::COMPONENTTYPE::TRANSFORM)
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::FixedUpdate()
	{
	}

	void Transform::Render()
	{
	}

	void Transform::SetConstantBuffer()
	{
	}

}
