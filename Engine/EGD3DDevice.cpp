﻿#include "pch.h"
#include "EGD3DDevice.hpp"
#include "../Client/CLApplication.hpp"
#include "EGRenderer.h"
#include "EGMesh.hpp"
#include "EGShader.hpp"

Engine::Graphics::D3DDevice::D3DDevice(HWND hwnd, UINT width, UINT height)
{
	m_hwnd_ = hwnd;
	m_width_ = width;
	m_height_ = height;

	UINT DeviceFlag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined( DEBUG ) || defined( _DEBUG )
	DeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	auto FeatureLevel = static_cast<D3D_FEATURE_LEVEL>(0);

	DX::ThrowIfFailed(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
	                                    , DeviceFlag, nullptr, 0
	                                    , D3D11_SDK_VERSION
	                                    , mDevice.GetAddressOf()
	                                    , &FeatureLevel
	                                    , mContext.GetAddressOf()));

#if defined( DEBUG ) || defined( _DEBUG )
	// Set up debug layer to break on D3D11 errors
	ID3D11Debug* d3dDebug = nullptr;
	mDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&d3dDebug));
	if (d3dDebug)
	{
		ID3D11InfoQueue* d3dInfoQueue = nullptr;
		if (SUCCEEDED(d3dDebug->QueryInterface(__uuidof(ID3D11InfoQueue), reinterpret_cast<void**>(&d3dInfoQueue))))
		{
			d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
			d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
			d3dInfoQueue->Release();
		}
		d3dDebug->Release();
	}
#endif

	DXGI_SWAP_CHAIN_DESC swapChainDesc{};

	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 144;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	CreateSwapChain(swapChainDesc);

	DX::ThrowIfFailed(
		mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(mFrameBuffer.GetAddressOf())));

	DX::ThrowIfFailed(
		mDevice->CreateRenderTargetView(mFrameBuffer.Get(), nullptr, mRenderTargetView.GetAddressOf()));

	// DepthStencilTexture
	D3D11_TEXTURE2D_DESC texdesc = {};

	texdesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	texdesc.Usage = D3D11_USAGE_DEFAULT;
	texdesc.CPUAccessFlags = 0;

	texdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texdesc.Width = width;
	texdesc.Height = height;
	texdesc.ArraySize = 1;

	texdesc.SampleDesc.Count = 1;
	texdesc.SampleDesc.Quality = 0;

	texdesc.MipLevels = 0;
	texdesc.MiscFlags = 0;

	CreateTexture(texdesc);
}

void Engine::Graphics::D3DDevice::CreateSwapChain(DXGI_SWAP_CHAIN_DESC& swapChainDesc)
{
	ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
	ComPtr<IDXGIAdapter> pAdapter = nullptr;
	ComPtr<IDXGIFactory> pFactory = nullptr;

	DX::ThrowIfFailed(mDevice->QueryInterface(__uuidof(IDXGIDevice),
	                                          reinterpret_cast<void**>(pDXGIDevice.GetAddressOf())));
	DX::ThrowIfFailed(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter),
	                                         reinterpret_cast<void**>(pAdapter.GetAddressOf())));
	DX::ThrowIfFailed(pAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf())));
	DX::ThrowIfFailed(pFactory->CreateSwapChain(mDevice.Get(), &swapChainDesc, mSwapChain.GetAddressOf()));
}

void Engine::Graphics::D3DDevice::CreateBuffer(const D3D11_BUFFER_DESC& desc,
                                               const D3D11_SUBRESOURCE_DATA* initial_data,
                                               ID3D11Buffer** buffer) const
{
	DX::ThrowIfFailed(mDevice->CreateBuffer(&desc, initial_data, buffer));
}

void Engine::Graphics::D3DDevice::CreateTexture(const D3D11_TEXTURE2D_DESC& desc)
{
	// Create Depth Stencil Buffer
	DX::ThrowIfFailed(mDevice->CreateTexture2D(&desc, nullptr, mDepthStencilBuffer.GetAddressOf()));

	// Create Depth Stencil Buffer View
	DX::ThrowIfFailed(
		mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf()));
}

void Engine::Graphics::D3DDevice::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
                                                    UINT NumElements, const void* pShaderBytecodeWithInputSignature,
                                                    SIZE_T BytecodeLength,
                                                    ID3D11InputLayout** ppInputLayout) const
{
	DX::ThrowIfFailed(mDevice->CreateInputLayout(pInputElementDescs, NumElements
	                                             , pShaderBytecodeWithInputSignature
	                                             , BytecodeLength
	                                             , ppInputLayout));
}

void Engine::Graphics::D3DDevice::CompileFromFile(const std::filesystem::path& fileName, const std::string& entrypoint,
                                                  const std::string& version, ID3DBlob** ppCode) const
{
	const std::filesystem::path path = std::filesystem::current_path().parent_path();
	const std::filesystem::path filePath = path / fileName;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ComPtr<ID3DBlob> errorBlob = nullptr;
	DX::ThrowIfFailed(D3DCompileFromFile(filePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
	                                     entrypoint.c_str(), version.c_str(), flags, 0, ppCode, &errorBlob));
}

void Engine::Graphics::D3DDevice::CreateVertexShader(ID3DBlob* pShaderBytecode,
                                                     ID3D11VertexShader** ppVertexShader) const
{
	DX::ThrowIfFailed(mDevice->CreateVertexShader(pShaderBytecode->GetBufferPointer()
	                                              , pShaderBytecode->GetBufferSize()
	                                              , nullptr
	                                              , ppVertexShader));
}

void Engine::Graphics::D3DDevice::CreatePixelShader(ID3DBlob* pShaderBytecode,
                                                    ID3D11PixelShader** ppPixelShader) const
{
	DX::ThrowIfFailed(mDevice->CreatePixelShader(pShaderBytecode->GetBufferPointer()
	                                             , pShaderBytecode->GetBufferSize()
	                                             , nullptr
	                                             , ppPixelShader));
}

void Engine::Graphics::D3DDevice::BindInputLayout(ID3D11InputLayout* pInputLayout) const
{
	mContext->IASetInputLayout(pInputLayout);
}

void Engine::Graphics::D3DDevice::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology) const
{
	mContext->IASetPrimitiveTopology(Topology);
}

void Engine::Graphics::D3DDevice::BindVertexBuffer(UINT startSlot, UINT numBuffers,
                                                   ID3D11Buffer* const* ppVertexBuffers, const UINT stride,
                                                   const UINT offset) const
{
	mContext->IASetVertexBuffers(startSlot, numBuffers, ppVertexBuffers, &stride, &offset);
}

void Engine::Graphics::D3DDevice::BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT format, UINT Offset) const
{
	mContext->IASetIndexBuffer(pIndexBuffer, format, Offset);
}

void Engine::Graphics::D3DDevice::BindVertexShader(ID3D11VertexShader* pVertexShader) const
{
	mContext->VSSetShader(pVertexShader, nullptr, 0);
}

void Engine::Graphics::D3DDevice::BindPixelShader(ID3D11PixelShader* pPixelShader) const
{
	mContext->PSSetShader(pPixelShader, nullptr, 0);
}

void Engine::Graphics::D3DDevice::BindViewports(D3D11_VIEWPORT* viewPort) const
{
	mContext->RSSetViewports(1, viewPort);
}

void Engine::Graphics::D3DDevice::BindConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size) const
{
	D3D11_MAPPED_SUBRESOURCE subRes = {};
	mContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
	memcpy(subRes.pData, data, size);
	mContext->Unmap(buffer, 0);
}

void Engine::Graphics::D3DDevice::SetConstantBuffer(ShaderStage stage, CBTYPES type, ID3D11Buffer** buffer) const
{
	switch (stage)
	{
	case ShaderStage::VS:
		{
			mContext->VSSetConstantBuffers(static_cast<UINT>(type), 1, buffer);
		}
		break;
	case ShaderStage::HS:
		{
			mContext->HSSetConstantBuffers(static_cast<UINT>(type), 1, buffer);
		}
		break;
	case ShaderStage::DS:
		{
			mContext->DSSetConstantBuffers(static_cast<UINT>(type), 1, buffer);
		}
		break;
	case ShaderStage::GS:
		{
			mContext->GSSetConstantBuffers(static_cast<UINT>(type), 1, buffer);
		}
		break;
	case ShaderStage::PS:
		{
			mContext->PSSetConstantBuffers(static_cast<UINT>(type), 1, buffer);
		}
		break;
	case ShaderStage::CS:
		{
			mContext->CSSetConstantBuffers(static_cast<UINT>(type), 1, buffer);
		}
		break;
	default:
		break;
	}
}

void Engine::Graphics::D3DDevice::Clear() const
{
	constexpr FLOAT backgroundColor[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	mContext->ClearRenderTargetView(mRenderTargetView.Get(), backgroundColor);
	mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void Engine::Graphics::D3DDevice::AdjustViewport()
{
	// ViewPort, RenderTaget
	RECT winRect;
	GetClientRect(m_hwnd_, &winRect);
	D3D11_VIEWPORT mViewPort = {
		0.0f, 0.0f, static_cast<FLOAT>(winRect.right - winRect.left), static_cast<FLOAT>(winRect.bottom - winRect.top)
	};
	BindViewports(&mViewPort);
	mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
}

void Engine::Graphics::D3DDevice::Draw(UINT VertexCount, UINT StartVertexLocation) const
{
	mContext->Draw(VertexCount, StartVertexLocation);
}

void Engine::Graphics::D3DDevice::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) const
{
	mContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void Engine::Graphics::D3DDevice::Present() const
{
	mSwapChain->Present(1, 0);
}

void Engine::Graphics::D3DDevice::Render() const
{
	Renderer::constantBuffers[static_cast<UINT>(CBTYPES::TRANSFORM)]->SetPipeline(ShaderStage::VS);

	Renderer::mesh.lock()->BindBuffer();
	DirectX::SimpleMath::Vector4 pos(0.0f, 0.0f, 0.0f, 0.0f);
	Renderer::constantBuffers[static_cast<UINT>(CBTYPES::TRANSFORM)]->Bind(&pos);

	Renderer::shader.lock()->Update();

	DrawIndexed(6, 0, 0);
}