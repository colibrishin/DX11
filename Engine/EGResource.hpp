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
		Resource(const std::wstring& name, const std::wstring& key, const std::filesystem::path& path) : Entity(name),
			mKey(key), mPath(path)
		{
		}

		~Resource() override = default;

	private:
		std::wstring mKey;
		std::filesystem::path mPath;
	};
}
