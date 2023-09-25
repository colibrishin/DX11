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

void GetBoundingBoxFromMesh(DirectX::BoundingBox& bb, const std::weak_ptr<Engine::Abstract::Mesh>& mesh)
{
	mesh.lock()->GetBoundingBox(bb);
}