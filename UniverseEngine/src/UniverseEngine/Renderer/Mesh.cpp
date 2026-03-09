#include "pch.h"
#include "Mesh.h"

namespace UniverseEngine {
	
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
		: m_Vertices(vertices), m_Indices(indices)
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
		
		if (!m_VertexBuffer)
		{
			m_VertexBuffer = std::make_shared<VertexBuffer>(Buffer(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex)));
			m_VertexBuffer->Bind();

			m_VertexArray->AddAttribute(AttributeType::Float3);
			m_VertexArray->AddAttribute(AttributeType::Float3);
			m_VertexArray->BakeLayout();
		}
		else
		{
			m_VertexBuffer->SetData(Buffer(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex)));
		}
		
		if (!m_IndexBuffer)
			m_IndexBuffer = std::make_shared<IndexBuffer>(Buffer(m_Indices.data(), m_Indices.size() * sizeof(uint32_t)));
		else
			m_IndexBuffer->SetData(Buffer(m_Indices.data(), m_Indices.size() * sizeof(uint32_t)));
	}
	
}
