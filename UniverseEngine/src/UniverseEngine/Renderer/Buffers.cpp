#include "pch.h"
#include "Buffers.h"

#include <glad/gl.h>

namespace UniverseEngine {

	VertexBuffer::VertexBuffer(const Buffer& buffer)
		: m_Size(static_cast<uint32_t>(buffer.Size))
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

	void VertexBuffer::SetData(const Buffer& buffer, uint32_t offset)
	{
		if (buffer.Size > m_Size)
			glNamedBufferData(m_BufferHandle, buffer.Size, nullptr, GL_STATIC_DRAW);
		glNamedBufferSubData(m_BufferHandle, offset, buffer.Size, buffer.Data);
	}

	IndexBuffer::IndexBuffer(const Buffer& buffer)
		: m_Size(static_cast<uint32_t>(buffer.Size))
	{
		glCreateBuffers(1, &m_BufferHandle);
		glNamedBufferData(m_BufferHandle, buffer.Size, nullptr, GL_STATIC_DRAW);
		glNamedBufferSubData(m_BufferHandle, 0, buffer.Size, buffer.Data);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferHandle);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferHandle);
	}

	void IndexBuffer::SetData(const Buffer& buffer, uint32_t offset)
	{
		if (buffer.Size > m_Size)
			glNamedBufferData(m_BufferHandle, buffer.Size, nullptr, GL_STATIC_DRAW);
		glNamedBufferSubData(m_BufferHandle, offset, buffer.Size, buffer.Data);
	}

	UniformBuffer::UniformBuffer(const Buffer& buffer)
	{
		glCreateBuffers(1, &m_BufferHandle);
		glNamedBufferData(m_BufferHandle, buffer.Size, nullptr, GL_STATIC_DRAW);
		glNamedBufferSubData(m_BufferHandle, 0, buffer.Size, buffer.Data);
	}

	UniformBuffer::~UniformBuffer()
	{
		glDeleteBuffers(1, &m_BufferHandle);
	}

	void UniformBuffer::Bind() const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_BufferHandle);
	}

	void UniformBuffer::BindToShader(uint32_t bindingPoint) const
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, m_BufferHandle);
	}

	void UniformBuffer::SetData(const Buffer& buffer, uint32_t offset) const
	{
		glNamedBufferSubData(m_BufferHandle, offset, buffer.Size, buffer.Data);
	}

}
