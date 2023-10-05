#include "pch.h"
#include <memory>
#include <vector>

#include "EGD3DDevice.hpp"
#include "EGGameObject.hpp"
#include "EGLayer.hpp"
#include "EGMesh.hpp"
#include "EGSceneManager.hpp"

Engine::Graphics::D3DDevice* GetDevice()
{
	return Engine::Graphics::D3DDevice::GetDevice();
}

UINT32 GetIDFromPointer(void* ptr)
{
	return reinterpret_cast<UINT64>(ptr) & 0xFFFFFFFF;
}

DirectX::SimpleMath::Vector3 GetMaxElementUnitVector(const DirectX::SimpleMath::Vector3& vec)
{
	return vec.x > vec.y ? (vec.x > vec.z ? DirectX::SimpleMath::Vector3::UnitX : DirectX::SimpleMath::Vector3::UnitZ) : (vec.y > vec.z ? DirectX::SimpleMath::Vector3::UnitY : DirectX::SimpleMath::Vector3::UnitZ);
}