#pragma once

#include "UniverseEngine/Core/Buffer.h"

namespace UniverseEngine {

	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		VertexBuffer(const Buffer& buffer);
		~VertexBuffer();

		void Bind() const;

		void SetData(const Buffer& buffer, uint32_t offset = 0);

		uint32_t GetHandle() const { return m_BufferHandle; }
	private:
		uint32_t m_BufferHandle = 0;
		uint32_t m_Size = 0;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer() = default;
		IndexBuffer(const Buffer& buffer);
		~IndexBuffer();

		void Bind() const;

		void SetData(const Buffer& buffer, uint32_t offset = 0);

		uint32_t GetHandle() const { return m_BufferHandle; }
	private:
		uint32_t m_BufferHandle = 0;
		size_t m_Size = 0;
	};

	class UniformBuffer
	{
	public:
		UniformBuffer() = default;
		UniformBuffer(const Buffer& buffer);
		~UniformBuffer();

		void Bind() const;
		void BindToShader(uint32_t bindingPoint) const;

		void SetData(const Buffer& buffer, uint32_t offset = 0) const;

		uint32_t GetHandle() const { return m_BufferHandle; }
	private:
		uint32_t m_BufferHandle = 0;
	};

}
