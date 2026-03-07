#pragma once

namespace UniverseEngine {

	enum class PrimitiveMode
	{
		None = 0,
		TriangleList, TriangleStrip, TriangleFan
	};

	class RendererAPI
	{
	public:
		static void Draw(uint32_t vertexCount, PrimitiveMode primitiveMode);
		static void DrawIndexed(uint32_t indexCount, PrimitiveMode primitiveMode);
	};

}
