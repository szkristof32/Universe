#pragma once

#include "UniverseEngine/Core/Window.h"
#include "UniverseEngine/Core/Reference.h"

namespace UniverseEngine {

	class Context
	{
	public:
		Context();
		~Context();

		void BeginFrame() const;
		void EndFrame() const;
	private:
		Reference<Window> m_Window;
	};

}
