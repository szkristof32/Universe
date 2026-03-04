#include "pch.h"
#include "VertexArray.h"

#include <glad/gl.h>

namespace UniverseEngine {

	namespace AttributeUtils {

		static uint32_t AttributeTypeSize(AttributeType type)
		{
			switch (type)
			{
				case AttributeType::Float:	return 1 * 4;
				case AttributeType::Float2:	return 2 * 4;
				case AttributeType::Float3:	return 3 * 4;
				case AttributeType::Float4:	return 4 * 4;
			}

			assert(false);
			return 0;
		}

		static uint32_t AttributeTypeComponentCount(AttributeType type)
		{
			switch (type)
			{
				case AttributeType::Float:	return 1;
				case AttributeType::Float2:	return 2;
				case AttributeType::Float3:	return 3;
				case AttributeType::Float4:	return 4;
			}

			assert(false);
			return 0;
		}

		static uint32_t AttributeTypeToGLType(AttributeType type)
		{
			switch (type)
			{
				case AttributeType::Float:
				case AttributeType::Float2:
				case AttributeType::Float3:
				case AttributeType::Float4:
					return GL_FLOAT;
			}

			assert(false);
			return 0;
		}

	}

	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_VertexArray);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArray);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_VertexArray);
	}

	void VertexArray::AddAttribute(AttributeType type)
	{
		VertexAttribute attribute{};
		attribute.Type = type;
		attribute.Size = AttributeUtils::AttributeTypeSize(type);
		attribute.Offset = m_Stride;
		m_Stride += attribute.Size;

		m_Attributes.emplace_back(attribute);
	}

	void VertexArray::BakeLayout() const
	{
		Bind();
		uint32_t location = 0;

		for (const auto& attribute : m_Attributes)
		{
			glEnableVertexAttribArray(location);
			glVertexAttribPointer(location, AttributeUtils::AttributeTypeComponentCount(attribute.Type),
								  AttributeUtils::AttributeTypeToGLType(attribute.Type), false,
								  m_Stride, (const void*)(size_t)attribute.Offset);
			location++;
		}
	}

}
