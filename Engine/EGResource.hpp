#pragma once
#include <filesystem>

#include "EGEntity.hpp"

namespace Engine::Abstract
{
	class Resource : public Entity
	{
	public:
		virtual void Load() = 0;

		const std::wstring& GetKey() { return mKey; }
		const std::filesystem::path& GetPath() { return mPath; }
		
		void SetKey(const std::wstring& key) { mKey = key; }
		void SetPath(const std::filesystem::path& path) { mPath = path; }

	protected:
		Resource(std::wstring name, std::wstring key, std::filesystem::path path) : Entity(std::move(name)),
			mKey(std::move(key)), mPath(std::move(path))
		{
		}

		~Resource() override = default;

	private:
		std::wstring mKey;
		std::filesystem::path mPath;
	};
}
