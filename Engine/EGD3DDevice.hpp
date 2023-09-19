#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <filesystem>
#include "EGGraphics.hpp"

namespace Engine::Graphics
{
	using namespace Microsoft::WRL;

	class D3DDevice
	{
	public:
		D3DDevice(const D3DDevice&) = default;
		~D3DDevice() = default;

		void CreateSwapChain(DXGI_SWAP_CHAIN_DESC& swapChainDesc);
		void CreateBuffer(const D3D11_BUFFER_DESC& desc, const D3D11_SUBRESOURCE_DATA* initial_data,
		                  ID3D11Buffer
		                  ** buffer) const;
		void CreateTexture(const D3D11_TEXTURE2D_DESC& desc, ID3D11Texture2D** texture) const;
		void CreateDepthStencil(const D3D11_TEXTURE2D_DESC& desc);
		void CreateShaderResourceView(ID3D11Texture2D* texture, const D3D11_SHADER_RESOURCE_VIEW_DESC& desc, ID3D11ShaderResourceView** resource_view) const;
		void GenerateMips(ID3D11ShaderResourceView* resource_view) const;
		void UpdateSubresource(ID3D11Resource* resource, void* data, const UINT stride, const UINT offset);
		void CreateSampler(const D3D11_SAMPLER_DESC& desc, ID3D11SamplerState** sampler_state) const;

		//bool CreateShader(const graphics::ShaderStage stage, const std::wstring& file, const std::string& funcName);
		void CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements
		                       , const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength,
		                       ID3D11InputLayout** ppInputLayout) const;
		void CompileFromFile(const std::filesystem::path& fileName, const std::string& entrypoint,
		                     const std::string& version, ID3DBlob
		                     ** ppCode) const;
		void CreateVertexShader(ID3DBlob* pShaderBytecode, ID3D11VertexShader** ppVertexShader) const;
		void CreatePixelShader(ID3DBlob* pShaderBytecode, ID3D11PixelShader** ppPixelShader) const;

		void BindInputLayout(ID3D11InputLayout* pInputLayout) const;
		void BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology) const;
		void BindVertexBuffer(UINT startSlot, UINT numBuffers, ID3D11Buffer* const* ppVertexBuffers, UINT stride,
		                      UINT offset = 0) const;
		void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT format, UINT Offset = 0) const;

		void BindVertexShader(ID3D11VertexShader* pVertexShader) const;
		void BindPixelShader(ID3D11PixelShader* pPixelShader) const;
		void BindSamplerState(ID3D11SamplerState** pSamplerState) const;
		void BIndPixelShaderResource(ID3D11ShaderResourceView** pResourceView) const;

		void BindViewports(D3D11_VIEWPORT* viewPort) const;
		void BindConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size) const;
		void SetConstantBuffer(ShaderStage stage, CBTYPES type, ID3D11Buffer** buffer) const;

		void Clear() const;
		void AdjustViewport();
		void Draw(UINT VertexCount, UINT StartVertexLocation) const;
		void DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) const;
		void Present() const;

		void Render() const;

		static void Initialize(HWND hwnd, UINT width, UINT height)
		{
			if (m_device_ == nullptr)
			{
				m_device_ = std::unique_ptr<D3DDevice>(new D3DDevice(hwnd, width, height));
			}
		}

		static D3DDevice* GetDevice()
		{
			return m_device_.get();
		}

	private:
		D3DDevice(HWND hwnd, UINT width, UINT height);

		inline static std::unique_ptr<D3DDevice> m_device_ = nullptr;

		HWND m_hwnd_;
		UINT m_width_;
		UINT m_height_;

		ComPtr<ID3D11Device> mDevice;
		ComPtr<ID3D11DeviceContext> mContext;
		ComPtr<ID3D11Texture2D> mFrameBuffer;
		ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
		ComPtr<ID3D11DepthStencilView> mDepthStencilView;
		ComPtr<IDXGISwapChain> mSwapChain;
		ComPtr<ID3D11SamplerState> mSamplers[static_cast<UINT>(Filter::MAXIMUM_ANISOTROPIC)];
	};
}
