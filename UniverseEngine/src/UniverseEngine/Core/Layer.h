#pragma once

#include "UniverseEngine/Core/Events/Event.h"
#include "UniverseEngine/Utils/StringView.h"

namespace UniverseEngine {

	class Layer
	{
	public:
		Layer() = default;
		Layer(StringView debugName)
			: m_DebugName(debugName)
		{
		}
		virtual ~Layer() = default;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate(float timestep) = 0;
		virtual void OnRender() = 0;
		virtual void OnEvent(Event& e) = 0;
	private:
		std::string m_DebugName;
	};

}
