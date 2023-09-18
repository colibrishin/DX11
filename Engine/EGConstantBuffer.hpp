#pragma once
#include "pch.h"
#include "EGD3DDevice.hpp"

namespace Engine::Graphics
{
	class ConstantBuffer : public GpuBuffer
	{
	public:
		ConstantBuffer() : mType(CBTYPES::NONE)
		{
		}

		~ConstantBuffer() override = default;

		void Create(size_t size);
		void Bind(void* data) const;
		void SetPipeline(ShaderStage stage);
		void Release() const;

	private:
		const CBTYPES mType;
	};

	inline void ConstantBuffer::Create(const size_t size)
	{
		const auto dev = D3DDevice::GetDevice();

		desc.ByteWidth = size;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		dev->CreateBuffer(desc, nullptr, buffer.GetAddressOf());
	}

	inline void ConstantBuffer::Bind(void* data) const
	{
		 D3DDevice::GetDevice()->BindConstantBuffer(buffer.Get(), data, desc.ByteWidth);
	}

	inline void ConstantBuffer::SetPipeline(ShaderStage stage)
	{
		 D3DDevice::GetDevice()->SetConstantBuffer(stage, mType, buffer.GetAddressOf());
	}

	inline void ConstantBuffer::Release() const
	{
		if(buffer)
		{
			buffer->Release();
		}
	}
}
