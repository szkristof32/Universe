#pragma once

#include "UniverseEngine/Core/Events/Event.h"

namespace UniverseEngine {

	class DebugEvent : public Event
	{
	public:
		DebugEvent(uint32_t debugCode)
			: m_DebugCode(debugCode)
		{
		}

		uint32_t GetDebugCode() const { return m_DebugCode; }

		UE_EVENT_TYPE(Debug);
		UE_EVENT_CATEGORY(EventCategory::Debug);
	private:
		uint32_t m_DebugCode;
	};

}
