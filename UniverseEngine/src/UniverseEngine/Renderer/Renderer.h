#pragma once

#include "UniverseEngine/Renderer/Context.h"

namespace UniverseEngine {

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void BeginFrame();
		void EndFrame();
	private:
		std::unique_ptr<Context> m_Context;
	};

}
