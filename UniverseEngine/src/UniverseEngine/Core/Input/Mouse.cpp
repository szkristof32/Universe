#include "pch.h"
#include "Mouse.h"

namespace UniverseEngine {

	void Mouse::Update()
	{
		m_ButtonsPressedThisFrame.clear();
		m_ButtonsReleasedThisFrame.clear();

		m_Dx = m_XPos - m_PrevX;
		m_Dy = m_YPos - m_PrevY;
		m_PrevX = m_XPos;
		m_PrevY = m_YPos;
		m_Scroll = 0;
	}

	void Mouse::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseMoveEvent>(UE_BIND_EVENT_FN(Mouse::OnMouseMove));
		dispatcher.Dispatch<MouseButtonPressEvent>(UE_BIND_EVENT_FN(Mouse::OnMouseButtonPress));
		dispatcher.Dispatch<MouseButtonReleaseEvent>(UE_BIND_EVENT_FN(Mouse::OnMouseButtonRelease));
		dispatcher.Dispatch<MouseScrollEvent>(UE_BIND_EVENT_FN(Mouse::OnMouseScroll));
	}

	bool Mouse::OnMouseMove(MouseMoveEvent& e)
	{
		m_XPos = e.GetX();
		m_YPos = e.GetY();

		return false;
	}

	bool Mouse::OnMouseButtonPress(MouseButtonPressEvent& e)
	{
		m_ButtonsDown.emplace((MouseButton)e.GetButton());
		m_ButtonsPressedThisFrame.emplace((MouseButton)e.GetButton());

		return false;
	}

	bool Mouse::OnMouseButtonRelease(MouseButtonReleaseEvent& e)
	{
		m_ButtonsDown.erase((MouseButton)e.GetButton());
		m_ButtonsReleasedThisFrame.emplace((MouseButton)e.GetButton());

		return false;
	}

	bool Mouse::OnMouseScroll(MouseScrollEvent& e)
	{
		m_Scroll = e.GetOffsetY();

		return false;
	}

}
