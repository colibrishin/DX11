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
		
		Renderer::Vertex m_vertex_[30] = {};
		const size_t m_vertex_count_ = std::size(m_vertex_);
		UINT m_index_[30] = {};
		const size_t m_index_count_ = std::size(m_index_);
	};

	inline void CircleMesh::generate_vertices()
	{
		// TODO: https://github.com/microsoft/DirectXTK12/wiki/GeometricPrimitive
		// TODO: Make it constant value.
		int n = 10; // number of triangles
		const float deltaTheta = DirectX::XM_2PI / n; // Change in theta for each vertex
		for (int i = 0; i < n; i++) 
		{
		    int theta = i * deltaTheta; // Theta is the angle for that triangle
		    int index = 3 * i;
			m_vertex_[index + 0] = Renderer::Vertex{{0, 0, 0}, {0.0f, 1.0f, 0.0f, 1.0f}};
		    // Given an angle theta, cosine [cos] will give you the x coordinate,
		    // and sine [sin] will give you the y coordinate.

			m_vertex_[index + 1] = Renderer::Vertex{
				{cosf(theta), sinf(theta), 0}, {0.0f, 1.0f, 0.0f, 1.0f}};
			m_vertex_[index + 2] = Renderer::Vertex{
				{cosf(theta + deltaTheta), sinf(theta + deltaTheta), 0}, {0.0f, 1.0f, 0.0f, 1.0f}};
		}
	}

	inline void CircleMesh::generate_indices()
	{
		// TODO
	}
}
