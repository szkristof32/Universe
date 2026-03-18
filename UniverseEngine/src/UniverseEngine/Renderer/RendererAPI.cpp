#include "pch.h"
#include "RendererAPI.h"

#include <glad/gl.h>

namespace UniverseEngine {

	namespace RendererAPIUtils {

		static uint32_t PrimitiveModeToGLMode(PrimitiveMode mode)
		{
			switch (mode)
			{
				case PrimitiveMode::TriangleList:	return GL_TRIANGLES;
				case PrimitiveMode::TriangleStrip:	return GL_TRIANGLE_STRIP;
				case PrimitiveMode::TriangleFan:	return GL_TRIANGLE_FAN;
				case PrimitiveMode::LineList:		return GL_LINES;
			}

			assert(false);
			return 0;
		}

	}

	RendererAPIConfiguration RendererAPI::s_Configuration{};

	void RendererAPI::Draw(uint32_t vertexCount, PrimitiveMode primitiveMode)
	{
		glDrawArrays(RendererAPIUtils::PrimitiveModeToGLMode(primitiveMode), 0, vertexCount);
	}

	void RendererAPI::DrawIndexed(uint32_t indexCount, PrimitiveMode primitiveMode)
	{
		glDrawElements(RendererAPIUtils::PrimitiveModeToGLMode(primitiveMode), indexCount, GL_UNSIGNED_INT, nullptr);
	}

	void RendererAPI::Configure()
	{
		if (s_Configuration.EnableDepthTest)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
		glDepthMask(s_Configuration.EnableDepthWrite);
		if (s_Configuration.BackfaceCulling)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		if (s_Configuration.EnableBlending)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glLineWidth(s_Configuration.LineWidth);
	}

}
