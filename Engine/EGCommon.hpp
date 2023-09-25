#pragma once

#include <SimpleMath.h>

#include "EGMesh.hpp"

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

struct UnionBoundingType
{
	Engine::Enums::BOUNDINGTYPE type;
	union
	{
		DirectX::BoundingSphere sphere;
		DirectX::BoundingOrientedBox box;
	};
};