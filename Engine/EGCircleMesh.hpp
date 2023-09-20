#pragma once
#include "pch.h"
#include <SimpleMath.h>
#include <string>
#include <GeometricPrimitive.h>

#include "../Engine/EGMeshRenderer.hpp"
#include "../Engine/EGRenderer.h"

namespace Engine::Mesh
{
	class CircleMesh : public Abstract::Mesh<Renderer::Vertex>
	{
	public:
		CircleMesh(const std::wstring& key) : Mesh(
			L"Circle", 
			key, 
			"", 
			m_vertex_, 
			&m_vertex_count_, 
			m_index_, 
			&m_index_count_)
		{
			generate_vertices();
			generate_indices();
		}
		~CircleMesh() override = default;

	private:
		void generate_vertices();
		void generate_indices();
		
		Renderer::Vertex m_vertex_[17] = {};
		const size_t m_vertex_count_ = std::size(m_vertex_);
		UINT m_index_[48] = {};
		const size_t m_index_count_ = std::size(m_index_);
	};

	inline void CircleMesh::generate_vertices()
	{
		// TODO: https://github.com/microsoft/DirectXTK12/wiki/GeometricPrimitive
		// TODO: Make it constant value.
		int n = 16; // number of triangles

		m_vertex_[0] = {{0, 0, 0,}, {0, 1, 0, 1}};

		const float deltaTheta = DirectX::XM_2PI / n; // Change in theta for each vertex
		for (int i = 1; i <= n; i++) 
		{
		    m_vertex_[i] = Renderer::Vertex{{cosf(deltaTheta * i), sinf(deltaTheta * i), 0}, {0.0f, 1.0f, 0.0f, 1.0f}};
		}
	}

	inline void CircleMesh::generate_indices()
	{
		int index = 0;
		int first = 1;
		int last = 2;

		for(int i = 0; i < 16; ++i)
		{
			m_index_[index] = 0;
			m_index_[index + 1] = first;
			m_index_[index + 2] = last;
			first = last;
			last += 1;

			// TODO: better recurrence relation
			std::swap(m_index_[index + 1], m_index_[index + 2]);

			index += 3;
		}

		m_index_[0] = 0;
		m_index_[46] = 1;
	}
}
