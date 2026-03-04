#include "pch.h"
#include "Buffers.h"

#include <glad/gl.h>

namespace UniverseEngine {

	VertexBuffer::VertexBuffer(const Buffer& buffer)
	{
		glCreateBuffers(1, &m_BufferHandle);
		glNamedBufferData(m_BufferHandle, buffer.Size, nullptr, GL_STATIC_DRAW);
		glNamedBufferSubData(m_BufferHandle, 0, buffer.Size, buffer.Data);
	}
	
	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferHandle);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferHandle);
	}

}
