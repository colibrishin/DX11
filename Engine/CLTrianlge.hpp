#pragma once
#include "pch.h"

#include <SimpleMath.h>
#include <string>

#include "../Engine/EGMeshRenderer.hpp"

namespace Client
{
	class Triangle : public Engine::Abstract::Mesh
	{
	public:
		Triangle(std::wstring name) : Mesh(
			std::move(name), 
			L"Triangle", 
			"", 
			m_vertex_, 
			&m_vertex_count_, 
			m_index_, 
			&m_index_count_)
		{
		}
		~Triangle() override = default;

	private:
		constexpr Engine::Renderer::Vertex m_vertex_[3] =
		{
			{{0.5f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
		};
		constexpr size_t m_vertex_count_ = sizeof(m_vertex_);
		constexpr UINT m_index_[3] = {0, 1, 2};
		constexpr size_t m_index_count_ = sizeof(m_index_);
	};
}
