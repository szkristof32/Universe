#pragma once

#include "UniverseEngine/Core/Layer.h"
#include "UniverseEngine/Core/Reference.h"

#include <vector>

namespace UniverseEngine {

	class LayerStack
	{
	public:
		void PushLayer(Reference<Layer> layer);
		void PushOverlay(Reference<Layer> overlay);
		void PopLayer(Reference<Layer> layer);
		void PopOverlay(Reference<Layer> overlay);

		std::vector<Reference<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<Reference<Layer>>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Reference<Layer>> m_Layers;
		size_t m_LayerInsertIndex = 0;
	};

}
