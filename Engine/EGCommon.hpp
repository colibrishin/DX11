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
constexpr float MAXIMUM_SPEED = 30.0f;

Engine::Graphics::D3DDevice* GetDevice();
UINT32 GetIDFromPointer(void* ptr);
DirectX::SimpleMath::Vector3 GetMaxElementUnitVector(const DirectX::SimpleMath::Vector3& vec);
bool AreVectorsParallel(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b);

template <typename T>
bool CheckPolarityFlip(const T& a, const T& b)
{
	return (a / -a) != (b / -b);
}

template <typename T>
T GetReversePolarityOf(const T& a)
{
	return (a / -a);
}