#pragma once

#include "UniverseEngine/Core/Events/Event.h"

namespace UniverseEngine {

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float x, float y)
			: m_XPos(x), m_YPos(y)
		{
		}

		float GetX() const { return m_XPos; }
		float GetY() const { return m_YPos; }

		UE_EVENT_TYPE(MouseMove);
		UE_EVENT_CATEGORY(EventCategory::Mouse);
	private:
		float m_XPos;
		float m_YPos;
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

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float offsetX, float offsetY)
			: m_OffsetX(offsetX), m_OffsetY(offsetY)
		{
		}

		float GetOffsetX() const { return m_OffsetX; }
		float GetOffsetY() const { return m_OffsetY; }

		UE_EVENT_TYPE(MouseScroll);
		UE_EVENT_CATEGORY(EventCategory::Mouse);
	private:
		float m_OffsetX;
		float m_OffsetY;
	};

}
