#pragma once

namespace UniverseEngine {

	enum class PrimitiveMode
	{
		None = 0,
		TriangleList, TriangleStrip, TriangleFan,
		LineList
	};

	struct RendererAPIConfiguration
	{
		bool EnableDepthTest = false;
		bool EnableDepthWrite = true;
		bool BackfaceCulling = true;
		bool EnableBlending = false;
		float LineWidth = 1.0f;
	};

	class RendererAPI
	{
	public:
		static void Draw(uint32_t vertexCount, PrimitiveMode primitiveMode);
		static void DrawIndexed(uint32_t indexCount, PrimitiveMode primitiveMode);

		static RendererAPIConfiguration& GetConfiguration() { return s_Configuration; }
		static void Configure();
	private:
		static RendererAPIConfiguration s_Configuration;
	};

}
