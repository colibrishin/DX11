#include "pch.h"
#include "EGD3DDevice.hpp"
#include "../Client/CLApplication.hpp"
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
	mDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(mDebug.GetAddressOf()));
	if (mDebug)
	{
		ID3D11InfoQueue* d3dInfoQueue = nullptr;
		if (SUCCEEDED(mDebug->QueryInterface(__uuidof(ID3D11InfoQueue), reinterpret_cast<void**>(&d3dInfoQueue))))
		{
			d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
			d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
			d3dInfoQueue->Release();
		}
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

	AdjustViewport();

	m_common_states_ = std::make_unique<DirectX::CommonStates>(mDevice.Get());
}

void Engine::Graphics::D3DDevice::ResizeSwapChain() const
{
#if defined( DEBUG ) || defined( _DEBUG )
	mDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
#endif

	DX::ThrowIfFailed(
		mSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0));
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

void Engine::Graphics::D3DDevice::CreateTexture(const D3D11_TEXTURE2D_DESC& desc, ID3D11Texture2D** texture) const
{
	DX::ThrowIfFailed(mDevice->CreateTexture2D(&desc, nullptr, texture));
}

void Engine::Graphics::D3DDevice::CreateDepthStencil(const D3D11_TEXTURE2D_DESC& desc)
{
	// Create Depth Stencil Buffer
	DX::ThrowIfFailed(mDevice->CreateTexture2D(&desc, nullptr, mDepthStencilBuffer.ReleaseAndGetAddressOf()));

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};

	depthStencilViewDesc.Format = desc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create Depth Stencil Buffer View
	DX::ThrowIfFailed(
		mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), &depthStencilViewDesc, mDepthStencilView.ReleaseAndGetAddressOf()));

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	DX::ThrowIfFailed(
		mDevice->CreateDepthStencilState(&depthStencilDesc, mDepthStencilState.ReleaseAndGetAddressOf()));

	mContext->OMSetDepthStencilState(mDepthStencilState.Get(), 1);
}

void Engine::Graphics::D3DDevice::CreateShaderResourceView(
	ID3D11Texture2D* texture, const D3D11_SHADER_RESOURCE_VIEW_DESC& desc, ID3D11ShaderResourceView** resource_view) const
{
	DX::ThrowIfFailed(mDevice->CreateShaderResourceView(
				texture, &desc, resource_view));
}

void Engine::Graphics::D3DDevice::GenerateMips(ID3D11ShaderResourceView* resource_view) const
{
	mContext->GenerateMips(resource_view);
}

void Engine::Graphics::D3DDevice::UpdateSubresource(ID3D11Resource* resource, void* data, const UINT stride, const UINT offset)
{
	mContext->UpdateSubresource(resource, 0, nullptr, data, stride, offset);
}

void Engine::Graphics::D3DDevice::CreateSampler(const D3D11_SAMPLER_DESC& desc, ID3D11SamplerState** sampler_state) const
{
	DX::ThrowIfFailed(mDevice->CreateSamplerState(&desc, sampler_state));
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

std::unique_ptr<DirectX::IEffectFactory> Engine::Graphics::D3DDevice::CreateEffectFactory() const
{
	return std::move(std::make_unique<DirectX::EffectFactory>(mDevice.Get()));
}

std::unique_ptr<DirectX::CommonStates> Engine::Graphics::D3DDevice::CreateCommonStates() const
{
	return std::move(std::make_unique<DirectX::CommonStates>(mDevice.Get()));
}

std::unique_ptr<DirectX::Model> Engine::Graphics::D3DDevice::LoadModelFromCMO(const std::filesystem::path& fileName,
                                                                              DirectX::IEffectFactory* effectFactory)
const
{
	const auto path = std::filesystem::absolute(fileName);
	auto model = DirectX::Model::CreateFromCMO(mDevice.Get(), path.c_str(), *effectFactory);

	if (model == nullptr)
	{
		throw std::exception("Failed to load model. See the debug output for more details.");
	}

	return std::move(model);
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

void Engine::Graphics::D3DDevice::BindSamplerState(ID3D11SamplerState** pSamplerState) const
{
	mContext->PSSetSamplers(0, 1, pSamplerState);
}

void Engine::Graphics::D3DDevice::BindPixelShaderResource(ID3D11ShaderResourceView** pResourceView) const
{
	mContext->PSSetShaderResources(0, 1, pResourceView);
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
	D3D11_VIEWPORT mViewPort = 
	{
		0.0f, 0.0f, static_cast<float>(m_width_), static_cast<float>(m_height_), 0.0f, 1.0f
	};

	BindViewports(&mViewPort);

	D3D11_TEXTURE2D_DESC texdesc = {};

	texdesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texdesc.Usage = D3D11_USAGE_DEFAULT;
	texdesc.CPUAccessFlags = 0;
	texdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texdesc.Width = m_width_;
	texdesc.Height = m_height_;
	texdesc.ArraySize = 1;
	texdesc.SampleDesc.Count = 1;
	texdesc.SampleDesc.Quality = 0;
	texdesc.MipLevels = 0;
	texdesc.MiscFlags = 0;

	CreateDepthStencil(texdesc);

	mContext->OMSetRenderTargets(1, 
		mRenderTargetView.GetAddressOf(), 
		mDepthStencilView.Get());
}

void Engine::Graphics::D3DDevice::Draw(UINT VertexCount, UINT StartVertexLocation) const
{
	mContext->Draw(VertexCount, StartVertexLocation);
}

void Engine::Graphics::D3DDevice::Draw(const DirectX::Model* model, const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& proj, const std::function<void(ID3D11Device*, ID3D11DeviceContext*, const DirectX::CommonStates*)>& customState, const bool wireframe) const
{
	model->Draw(
		mContext.Get(), 
		*m_common_states_, 
		world, 
		view, 
		proj, 
		wireframe, 
		[&]()
		{
			customState(mDevice.Get(), mContext.Get(), m_common_states_.get());
		});
}

void Engine::Graphics::D3DDevice::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) const
{
	mContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void Engine::Graphics::D3DDevice::Present() const
{
	mSwapChain->Present(1, 0);
}

void Engine::Graphics::D3DDevice::Resize(UINT width, UINT height)
{
	m_width_ = width;
	m_height_ = height;

	mContext->OMSetRenderTargets(0, nullptr, nullptr);
	mRenderTargetView->Release();
	mFrameBuffer->Release();

	ResizeSwapChain();

	DX::ThrowIfFailed(
		mSwapChain->GetBuffer(
			0, 
			__uuidof(ID3D11Texture2D), 
			reinterpret_cast<void**>(mFrameBuffer.GetAddressOf())));

	DX::ThrowIfFailed(
		mDevice->CreateRenderTargetView(
			mFrameBuffer.Get(), 
			nullptr, 
			mRenderTargetView.GetAddressOf()));

	AdjustViewport();

	m_resized_ = false;
}

std::unique_ptr<DirectX::GeometricPrimitive> Engine::Graphics::D3DDevice::CreateBox(const DirectX::XMFLOAT3& size) const
{
	return std::move(DirectX::GeometricPrimitive::CreateBox(mContext.Get(), size));
}
