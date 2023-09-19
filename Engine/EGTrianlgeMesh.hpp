#pragma once
#include "pch.h"

#include <string>

#include "../Engine/EGMeshRenderer.hpp"
#include "../Engine/EGRenderer.h"

namespace Engine::Mesh
{
	class TriangleMesh : public Abstract::Mesh<Renderer::Vertex>
	{
	public:
		TriangleMesh(const std::wstring& key) : Mesh(
			L"Triangle", 
			key, 
			"", 
			m_vertex_, 
			&m_vertex_count_, 
			m_index_, 
			&m_index_count_)
		{
		}
		~TriangleMesh() override = default;

	private:
		const Renderer::Vertex m_vertex_[3] =
		{
			{{0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
			{{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
		};
		const size_t m_vertex_count_ = std::size(m_vertex_);
		const UINT m_index_[3] = {0, 1, 2};
		const size_t m_index_count_ = std::size(m_index_);
	};
}
