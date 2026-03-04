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

}
