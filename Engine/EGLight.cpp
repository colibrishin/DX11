#include "pch.h"
#include "EGLight.hpp"

Engine::Object::Light::Light(const std::wstring& name) : GameObject(name), m_lightBuffer_()
{
}

void Engine::Object::Light::SetDiffuseColor(DirectX::XMFLOAT4 color)
{
	m_lightBuffer_.diffuseColor = color;
}

void Engine::Object::Light::SetDirection(DirectX::XMFLOAT3 dir)
{
	m_lightBuffer_.lightDirection = dir;
}

DirectX::XMFLOAT3 Engine::Object::Light::GetDirection() const
{
	return m_lightBuffer_.lightDirection;
}

Engine::Renderer::LightBuffer& Engine::Object::Light::GetLightBuffer()
{
	return m_lightBuffer_;
}

DirectX::XMFLOAT4 Engine::Object::Light::GetDiffuseColor() const
{
    return m_lightBuffer_.diffuseColor;
}
