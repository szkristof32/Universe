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
			}

			assert(false);
			return 0;
		}

	}

	void RendererAPI::Draw(uint32_t vertexCount, PrimitiveMode primitiveMode)
	{
		glDrawArrays(RendererAPIUtils::PrimitiveModeToGLMode(primitiveMode), 0, vertexCount);
	}

	void RendererAPI::DrawIndexed(uint32_t indexCount, PrimitiveMode primitiveMode)
	{
		glDrawElements(RendererAPIUtils::PrimitiveModeToGLMode(primitiveMode), indexCount, GL_UNSIGNED_INT, nullptr);
	}

}
