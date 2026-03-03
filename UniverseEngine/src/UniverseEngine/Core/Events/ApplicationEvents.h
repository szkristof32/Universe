#pragma once

#include "UniverseEngine/Core/Events/Event.h"

namespace UniverseEngine {

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		UE_EVENT_TYPE(WindowClose);
		UE_EVENT_CATEGORY(EventCategory::Application);
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height)
		{
		}

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		UE_EVENT_TYPE(WindowResize);
		UE_EVENT_CATEGORY(EventCategory::Application);
	private:
		uint32_t m_Width;
		uint32_t m_Height;
	};

}
