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

		uint32_t GetHandle() const { return m_BufferHandle; }
	private:
		uint32_t m_BufferHandle = 0;
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
