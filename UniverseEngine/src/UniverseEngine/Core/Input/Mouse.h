#pragma once

#include "UniverseEngine/Core/Events/MouseEvents.h"

namespace UniverseEngine {

	enum class MouseButton
	{
		None = -1,
		Left, Middle, Right
	};

	class Mouse
	{
	public:
		Mouse() noexcept = default;

		void Update();

		bool IsButtonDown(MouseButton button) { return m_ButtonsDown.find(button) != m_ButtonsDown.end(); }
		bool IsButtonPressed(MouseButton button) { return m_ButtonsPressedThisFrame.find(button) != m_ButtonsPressedThisFrame.end(); }
		bool IsButtonReleased(MouseButton button) { return m_ButtonsReleasedThisFrame.find(button) != m_ButtonsReleasedThisFrame.end(); }

		float GetX() const { return m_XPos; }
		float GetY() const { return m_YPos; }
		float GetDx() const { return m_Dx; }
		float GetDy() const { return m_Dy; }
		float GetScroll() const { return m_Scroll; }

		void OnEvent(Event& e);
	private:
		bool OnMouseMove(MouseMoveEvent& e);
		bool OnMouseButtonPress(MouseButtonPressEvent& e);
		bool OnMouseButtonRelease(MouseButtonReleaseEvent& e);
		bool OnMouseScroll(MouseScrollEvent& e);
	private:
		std::unordered_set<MouseButton> m_ButtonsDown;
		std::unordered_set<MouseButton> m_ButtonsPressedThisFrame;
		std::unordered_set<MouseButton> m_ButtonsReleasedThisFrame;

		float m_XPos, m_YPos;
		float m_Dx, m_Dy;
		float m_Scroll;
		float m_PrevX, m_PrevY;
	};

}
