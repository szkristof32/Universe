#include "pch.h"
#include "LayerStack.h"

namespace UniverseEngine {

	void LayerStack::PushLayer(std::unique_ptr<Layer>&& layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(std::unique_ptr<Layer>&& overlay)
	{
		m_Layers.emplace_back(std::move(overlay));
	}

	void LayerStack::PopLayer(Reference<Layer> layer)
	{
		for (uint32_t i = 0; i < m_LayerInsertIndex; i++)
		{
			if (m_Layers[i].get() == layer.Get())
			{
				m_Layers.erase(m_Layers.begin() + i);
				return;
			}
		}
	}

	void LayerStack::PopOverlay(Reference<Layer> overlay)
	{
		for (uint32_t i = m_LayerInsertIndex; i < m_Layers.size(); i++)
		{
			if (m_Layers[i].get() == overlay.Get())
			{
				m_Layers.erase(m_Layers.begin() + i);
				return;
			}
		}
	}

	void LayerStack::PopAll()
	{
		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); it++)
			(*it)->OnDetach();
		m_Layers.clear();
	}

}
