#include "pch.h"
#include "Mesh.h"

namespace UniverseEngine {
	
	Mesh::Mesh(const std::vector<Vertex>& vertices)
		: m_Vertices(vertices)
	{
		Invalidate();
	}

	void Mesh::Invalidate()
	{
		m_VertexBuffer.reset();
		m_IndexBuffer.reset();

		if (!m_VertexArray)
			m_VertexArray = std::make_shared<VertexArray>();
		m_VertexArray->Bind();
		
		ProcessVertices();
		
		if (!m_VertexBuffer)
		{
			m_VertexBuffer = std::make_shared<VertexBuffer>(Buffer(m_UniqueVertices.data(), m_UniqueVertices.size() * sizeof(Vertex)));
			m_VertexBuffer->Bind();

			m_VertexArray->AddAttribute(AttributeType::Float3);
			m_VertexArray->AddAttribute(AttributeType::Float3);
			m_VertexArray->BakeLayout();
		}
		else
		{
			m_VertexBuffer->SetData(Buffer(m_UniqueVertices.data(), m_UniqueVertices.size() * sizeof(Vertex)));
		}
		
		if (!m_IndexBuffer)
			m_IndexBuffer = std::make_shared<IndexBuffer>(Buffer(m_Indices.data(), m_Indices.size() * sizeof(uint32_t)));
		else
			m_IndexBuffer->SetData(Buffer(m_Indices.data(), m_Indices.size() * sizeof(uint32_t)));
	}

	void Mesh::ProcessVertices()
	{
		m_UniqueVertices.clear();
		m_Indices.clear();

		for (uint32_t i = 0; i < m_Vertices.size(); i++)
		{
			const auto& vertex = m_Vertices[i];

			uint32_t index = i;

			auto it = std::find(m_UniqueVertices.begin(), m_UniqueVertices.end(), vertex);
			if (it == m_UniqueVertices.end())
				m_UniqueVertices.emplace_back(vertex);
			else
				index = m_UniqueVertices.begin() - it;

			m_Indices.emplace_back(index);
		}
	}
	
}
