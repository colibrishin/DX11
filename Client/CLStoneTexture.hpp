#pragma once
#include "pch.h"
#include "../Engine/EGTexture2D.hpp"

namespace Client::Texture
{
	class StoneTexture final : public Engine::Graphics::Texture2D
	{
	public:
		StoneTexture(const std::wstring& key);
		~StoneTexture() override = default;
	};

	inline StoneTexture::StoneTexture(const std::wstring& key) : Texture2D(L"Stone Texture", key, "stone01.tga")
	{
	}
}
