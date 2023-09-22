#include "pch.h"
#include "EGLight.hpp"

Engine::Object::Light::Light(const std::wstring& name) : GameObject(name), m_diffuseColor_(), m_direction_()
{
}

void Engine::Object::Light::SetDiffuseColor(DirectX::XMFLOAT4 color)
{
	m_diffuseColor_ = color;
}

void Engine::Object::Light::SetDirection(DirectX::XMFLOAT3 dir)
{
	m_direction_ = dir;
}

DirectX::XMFLOAT3 Engine::Object::Light::GetDirection() const
{
	return m_direction_;
}

DirectX::XMFLOAT4 Engine::Object::Light::GetDiffuseColor() const
{
    return m_diffuseColor_;
}
