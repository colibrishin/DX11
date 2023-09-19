#pragma once
#include "pch.h"

#include <string>

#include "../Engine/EGMeshRenderer.hpp"
#include "../Engine/EGRenderer.h"

namespace Engine::Mesh
{
	class SquareMesh : public Abstract::Mesh<Renderer::Vertex>
	{
	public:
		SquareMesh(const std::wstring& key) : Mesh(
			L"Square", 
			key, 
			"", 
			m_vertex_, 
			&m_vertex_count_, 
			m_index_, 
			&m_index_count_)
		{
		}
		~SquareMesh() override = default;

	private:
		const Renderer::Vertex m_vertex_[4] =
		{
			{{-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{-1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}}
		};
		const size_t m_vertex_count_ = std::size(m_vertex_);
		const UINT m_index_[6] = {0, 1, 2, 0, 2, 3};
		const size_t m_index_count_ = std::size(m_index_);
	};
}
