#include "pch.h"
#include "RendererAPI.h"

#include <glad/gl.h>

namespace UniverseEngine {

	void RendererAPI::Draw(uint32_t vertexCount)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexCount);
	}

}
