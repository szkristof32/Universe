#pragma once

#include "UniverseEngine/Renderer/Buffers.h"
#include "UniverseEngine/Renderer/VertexArray.h"

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace UniverseEngine {

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
	};

	inline bool operator==(const Vertex& a, const Vertex& b)
	{
		return a.Position == b.Position && a.Normal == b.Position;
	}
	inline bool operator!=(const Vertex& a, const Vertex& b)
	{
		return !(a == b);
	}

	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(const std::vector<Vertex>& vertices);

		std::vector<Vertex>& GetVertices() { return m_Vertices; }
		const std::vector<Vertex>& GetVertices() const { return m_Vertices; }

		std::shared_ptr<VertexArray> GetVertexArray() const { return m_VertexArray; }
		std::shared_ptr<VertexBuffer> GetVertexBuffer() const { return m_VertexBuffer; }
		std::shared_ptr<IndexBuffer> GetIndexBuffer() const { return m_IndexBuffer; }

		void Invalidate();
	private:
		void ProcessVertices();
	private:
		std::vector<Vertex> m_Vertices;

		std::vector<Vertex> m_UniqueVertices;
		std::vector<uint32_t> m_Indices;

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexArray> m_VertexArray;
	};

}
