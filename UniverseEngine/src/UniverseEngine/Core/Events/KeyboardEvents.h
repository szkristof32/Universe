#pragma once

#include "UniverseEngine/Core/Events/Event.h"

namespace UniverseEngine {

	class KeyEvent : public Event
	{
	public:
		KeyEvent(uint32_t keyCode)
			: m_KeyCode(keyCode)
		{
		}

		uint32_t GetKeyCode() const { return m_KeyCode; }

		UE_EVENT_CATEGORY(EventCategory::Keyboard);
	protected:
		uint32_t m_KeyCode;
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(uint32_t keyCode, bool repeat = false)
			: KeyEvent(keyCode), m_Repeat(repeat)
		{
		}

		bool DoesRepeat() const { return m_Repeat; }

		UE_EVENT_TYPE(KeyPress);
	private:
		bool m_Repeat;
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(uint32_t keyCode)
			: KeyEvent(keyCode)
		{
		}

		UE_EVENT_TYPE(KeyRelease);
	};

	class KeyTypeEvent : public KeyEvent
	{
	public:
		KeyTypeEvent(uint32_t keyCode, bool repeat = false)
			: KeyEvent(keyCode), m_Repeat(repeat)
		{
		}

		char GetTypedCharacter() const { return (char)m_KeyCode; }
		bool DoesRepeat() const { return m_Repeat; }

		UE_EVENT_TYPE(KeyType);
	private:
		bool m_Repeat;
	};

}
