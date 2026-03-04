#pragma once

namespace UniverseEngine {

	enum class AttributeType
	{
		None = 0,
		Float, Float2, Float3, Float4,
	};

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;

		void AddAttribute(AttributeType type);
		void BakeLayout() const;
	private:
		uint32_t m_VertexArray = 0;

		struct VertexAttribute
		{
			AttributeType Type;
			uint32_t Size;
			uint32_t Offset;
		};
		std::vector<VertexAttribute> m_Attributes;
		uint32_t m_Stride = 0;
	};

}
