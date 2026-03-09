#pragma once

namespace UniverseEngine {

	enum class PrimitiveMode
	{
		None = 0,
		TriangleList, TriangleStrip, TriangleFan
	};

	struct RendererAPIConfiguration
	{
		bool EnableDepthTest = false;
		bool EnableDepthWrite = true;
		bool BackfaceCulling = true;
		bool EnableBlending = false;
	};

	class RendererAPI
	{
	public:
		static void Draw(uint32_t vertexCount, PrimitiveMode primitiveMode);
		static void DrawIndexed(uint32_t indexCount, PrimitiveMode primitiveMode);

		static void Configure(const RendererAPIConfiguration& configuration);
	};

}
