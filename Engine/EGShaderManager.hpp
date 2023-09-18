#pragma once
#include "pch.h"

#include "EGResource.hpp"
#include "EGScene.hpp"
#include "EGShader.hpp"

namespace Engine::Manager
{
	class ShaderManager
	{
	public:
		ShaderManager() = delete;
		~ShaderManager() = delete;

		template <typename T>
		static std::weak_ptr<T> Find(const std::wstring& name)
		{
			const auto iter = mShaders.find(name);

			if (iter != mShaders.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			return nullptr;
		}

		template <typename T>
		static std::weak_ptr<T> Add(const std::wstring& name)
		{
			std::weak_ptr<T> shader = Find<T>(name);
			if (shader.lock())
			{
				return shader;
			}

			shader = new T();
			mShaders.insert({name, std::shared_ptr<T>(shader)});

			return shader;
		}

	private:
		inline static std::map<std::wstring, std::shared_ptr<Abstract::Shader>> mShaders{};
	};
}
