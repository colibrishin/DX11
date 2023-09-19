#pragma once
#include "EGD3DDevice.hpp"
#include "EGResource.hpp"

namespace Engine::Abstract
{
	using namespace Microsoft::WRL;

	class Shader : public Resource
	{
	public:
		void Load() override;

		void Create(const Graphics::ShaderStage stage, const std::filesystem::path& file, const std::string& entrypoint);
		virtual void Update();
		[[nodiscard]] Graphics::ShaderStage GetStage() const { return mStage; }

	protected:
		Shader(const std::wstring& name, 
		const std::wstring& key, 
		const std::filesystem::path& path,
		D3D11_PRIMITIVE_TOPOLOGY topology,
		const D3D11_INPUT_ELEMENT_DESC* input_desc, 
		const size_t* input_size, 
		const Graphics::ShaderStage stage,
		const std::string& entrypoint);

		~Shader() override = default;

		ID3D11InputLayout* GetInputLayout() const
		{
			return mInputLayout.Get();
		}
		ID3D11InputLayout** GetInputLayoutAddressOf()
		{
			return mInputLayout.GetAddressOf();
		}

		ID3DBlob* GetVSCode() const
		{
			return mVSBlob.Get();
		}

	private:
		const std::string m_entry_point_;
		const D3D11_INPUT_ELEMENT_DESC* mInputDesc;
		const size_t* mInputSize;

		ComPtr<ID3D11InputLayout> mInputLayout;
		D3D11_PRIMITIVE_TOPOLOGY mTopology;
		Graphics::ShaderStage mStage;

		ComPtr<ID3DBlob> mVSBlob;
		ComPtr<ID3DBlob> mHSBlob;
		ComPtr<ID3DBlob> mDSBlob;
		ComPtr<ID3DBlob> mGSBlob;
		ComPtr<ID3DBlob> mPSBlob;

		ComPtr<ID3DBlob> mErrorBlob;

		ComPtr<ID3D11VertexShader> mVS;
		ComPtr<ID3D11HullShader> mHS;
		ComPtr<ID3D11DomainShader> mDS;
		ComPtr<ID3D11GeometryShader> mGS;
		ComPtr<ID3D11PixelShader> mPS;
	};

	inline Shader::Shader(
		const std::wstring& name, 
		const std::wstring& key, 
		const std::filesystem::path& path,
		D3D11_PRIMITIVE_TOPOLOGY topology,
		const D3D11_INPUT_ELEMENT_DESC* input_desc, 
		const size_t* input_size, 
		const Graphics::ShaderStage stage,
		const std::string& entrypoint) : Resource(name, key, path),
		m_entry_point_(entrypoint), mTopology(topology), mInputDesc(input_desc), mInputSize(input_size), mStage(stage)
	{
	}

	inline void Shader::Load()
	{
		Create(mStage, GetPath(), m_entry_point_);
	}

	inline void Shader::Create(const Graphics::ShaderStage stage, const std::filesystem::path& file,
		const std::string& entrypoint)
	{
		std::filesystem::path path = std::filesystem::current_path().parent_path();
		std::filesystem::path shaderPath = path / file;

		if (stage == Graphics::ShaderStage::VS)
		{
			Graphics::D3DDevice::GetDevice()->CompileFromFile(file, entrypoint, "vs_5_0", mVSBlob.GetAddressOf());
			Graphics::D3DDevice::GetDevice()->CreateInputLayout(
				mInputDesc, *mInputSize, mVSBlob->GetBufferPointer(), mVSBlob->GetBufferSize(), mInputLayout.GetAddressOf());
			Graphics::D3DDevice::GetDevice()->CreateVertexShader(mVSBlob.Get(), mVS.GetAddressOf());
		}
		
		if (stage == Graphics::ShaderStage::PS)
		{
			Graphics::D3DDevice::GetDevice()->CompileFromFile(file, entrypoint, "ps_5_0", mPSBlob.GetAddressOf());
			Graphics::D3DDevice::GetDevice()->CreatePixelShader(mPSBlob.Get(), mPS.GetAddressOf());
		}
	}

	inline void Shader::Update()
	{
		if(mVS != nullptr)
		{
			Graphics::D3DDevice::GetDevice()->BindPrimitiveTopology(mTopology);
			Graphics::D3DDevice::GetDevice()->BindInputLayout(mInputLayout.Get());
			Graphics::D3DDevice::GetDevice()->BindVertexShader(mVS.Get());
		}
		if(mPS != nullptr)
		{
			Graphics::D3DDevice::GetDevice()->BindPixelShader(mPS.Get());
		}
	}
}
