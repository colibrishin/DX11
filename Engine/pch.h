// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H
#define arraysize(a) (sizeof(a) / sizeof(a[0]))

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"

#include <Keyboard.h>
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>

#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <type_traits>
#include <map>
#include <vector>
#include <memory>

#include <algorithm>
#include <execution>

#include "BufferHelpers.h"
#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "DirectXHelpers.h"
#include "Effects.h"
#include "GamePad.h"
#include "GeometricPrimitive.h"
#include "GraphicsMemory.h"
#include "Keyboard.h"
#include "Model.h"
#include "Mouse.h"
#include "PostProcess.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"
#include "WICTextureLoader.h"

#include "EGCommon.hpp"

#include <DirectXTex.h>

#include <exception>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

struct MatrixBufferType
{
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
};

struct ColorVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};

struct TextureVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 texture;
};

namespace DX
{
	// Enable enum flags:
	// https://www.justsoftwaresolutions.co.uk/cplusplus/using-enum-classes-as-bitfields.html

	template<typename E>
	struct enable_bitmask_operators 
	{
		static constexpr bool enable = false;
	};

	template<typename E>
	constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator|(E lhs, E rhs)
	{
		typedef typename std::underlying_type<E>::type underlying;
		return static_cast<E>
			( 
				static_cast<underlying>(lhs) | static_cast<underlying>(rhs) 
			);
	}

	template<typename E>
	constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator|=(E& lhs, E rhs)
	{
		typedef typename std::underlying_type<E>::type underlying;
		lhs = static_cast<E>
			( 
				static_cast<underlying>(lhs) | static_cast<underlying>(rhs) 
			);

		return lhs;
	}

	template<typename E>
	constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator&(E lhs, E rhs)
	{
		typedef typename std::underlying_type<E>::type underlying;
		return static_cast<E>
			( 
				static_cast<underlying>(lhs) & static_cast<underlying>(rhs) 
			);
	}

	template<typename E>
	constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator&=(E& lhs, E rhs)
	{
		typedef typename std::underlying_type<E>::type underlying;
		lhs = static_cast<E>
			(
				static_cast<underlying>(lhs) & static_cast<underlying>(rhs)
			);

		return lhs;
	}

	template<typename E>
	constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator~(E rhs)
	{
		typedef typename std::underlying_type<E>::type underlying;
		rhs = static_cast<E>
			(
				~static_cast<underlying>(rhs)
			);
		
		return rhs;
	}

	template<typename E>
	constexpr bool has_flag(E lhs, E rhs)
	{
		return (lhs & rhs) == rhs;
	}

	// Helper class for COM exceptions
	class com_exception : public std::exception
	{
	public:
		com_exception(HRESULT hr) : result(hr)
		{
		}

		const char* what() const override
		{
			static char s_str[64] = {};
			sprintf_s(s_str, "Failure with HRESULT of %08X",
			          static_cast<unsigned int>(result));
			return s_str;
		}

	private:
		HRESULT result;
	};

	// Helper utility converts D3D API failures into exceptions.
	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw com_exception(hr);
		}
	}
}

#endif //PCH_H
