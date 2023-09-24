#pragma once

#include <SimpleMath.h>

namespace Engine::Abstract
{
	class GameObject;
}

namespace Engine
{
	namespace Graphics
	{
		class D3DDevice;
	}
}

constexpr float fov = DirectX::XM_PI / 4;
constexpr float nearZ = 0.3f;
constexpr float farZ = 1000.0f;
constexpr float GRAVITY_ACCEL = 9.8f;

Engine::Graphics::D3DDevice* GetDevice();
UINT32 GetIDFromPointer(void* ptr);