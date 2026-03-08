#pragma once

#include "UniverseEngine/Core/Layer.h"
#include "UniverseEngine/Core/Reference.h"

#include <vector>

namespace UniverseEngine {

	class LayerStack
	{
	public:
		void PushLayer(std::unique_ptr<Layer>&& layer);
		void PushOverlay(std::unique_ptr<Layer>&& overlay);
		void PopLayer(Reference<Layer> layer);
		void PopOverlay(Reference<Layer> overlay);

		std::vector<std::unique_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<std::unique_ptr<Layer>>::iterator end() { return m_Layers.end(); }
		std::vector<std::unique_ptr<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<std::unique_ptr<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }

		void PopAll();
	private:
		std::vector<std::unique_ptr<Layer>> m_Layers;
		size_t m_LayerInsertIndex = 0;
	};

}
