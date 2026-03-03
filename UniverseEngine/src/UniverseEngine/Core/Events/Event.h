#pragma once

#include "UniverseEngine/Core/Base.h"

#include <string>

namespace UniverseEngine {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize,
		MouseMove, MouseButtonPress, MouseButtonRelease, MouseScroll,
		KeyPress, KeyRelease, KeyType,
		Debug
	};

	enum class EventCategory
	{
		None = 0,
		Application	= Bitfield(0),
		Mouse		= Bitfield(1),
		Keyboard	= Bitfield(2),
		Input		= Mouse | Keyboard,
		Debug		= Bitfield(3)
	};

	// TODO: create string view
#define UE_EVENT_TYPE(type) virtual EventType GetType() const override { return EventType::type; } \
							static EventType GetStaticType() { return EventType::type; } \
							virtual const char* GetName() const override { return #type; }
#define UE_EVENT_CATEGORY(category)	virtual EventCategory GetCategory() const override { return category; }

#define UE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType GetType() const = 0;
		virtual EventCategory GetCategory() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
	public:
		bool Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename _Ty, typename _Fn>
		bool Dispatch(_Fn fn)
		{
			if (!m_Event.Handled && _Ty::GetStaticType() == m_Event.GetType())
			{
				m_Event.Handled |= fn((_Ty&)m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

}
