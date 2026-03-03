#pragma once

#include "UniverseEngine/Core/Events/Event.h"

namespace UniverseEngine {

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(uint32_t x, uint32_t y)
			: m_XPos(x), m_YPos(y)
		{
		}

		uint32_t GetX() const { return m_XPos; }
		uint32_t GetY() const { return m_YPos; }

		UE_EVENT_TYPE(MouseMove);
		UE_EVENT_CATEGORY(EventCategory::Mouse);
	private:
		uint32_t m_XPos;
		uint32_t m_YPos;
	};

	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(uint32_t button)
			: m_Button(button)
		{
		}

		uint32_t GetButton() const { return m_Button; }

		UE_EVENT_CATEGORY(EventCategory::Mouse);
	protected:
		uint32_t m_Button;
	};

	class MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(uint32_t button)
			: MouseButtonEvent(button)
		{
		}

		UE_EVENT_TYPE(MouseButtonPress);
	};

	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(uint32_t button)
			: MouseButtonEvent(button)
		{
		}

		UE_EVENT_TYPE(MouseButtonRelease);
	};

}
