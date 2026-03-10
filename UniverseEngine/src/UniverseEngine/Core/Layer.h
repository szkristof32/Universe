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

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep delta) {};
		virtual void OnRender() {};
		virtual void OnUIRender() {};
		virtual void OnEvent(Event& e) {};
	private:
		std::string m_DebugName;
	};

}
