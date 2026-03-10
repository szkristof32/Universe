#pragma once

#include "UniverseEngine/Core/Input/Keyboard.h"
#include "UniverseEngine/Core/Input/Mouse.h"

namespace UniverseEngine {

	class Input
	{
	public:
		static void Update();
		static void OnEvent(Event& e);

		static bool IsKeyDown(Key key) { return s_Keyboard.IsKeyDown(key); }
		static bool IsKeyPressed(Key key, bool checkRepeats = false) { return s_Keyboard.IsKeyPressed(key, checkRepeats); }
		static bool IsKeyReleased(Key key) { return s_Keyboard.IsKeyReleased(key); }

		static const std::vector<Key>& GetTypedKeys() { return s_Keyboard.GetTypedKeys(); }

		static bool IsButtonDown(MouseButton button) { return s_Mouse.IsButtonDown(button); }
		static bool IsButtonPressed(MouseButton button) { return s_Mouse.IsButtonPressed(button); }
		static bool IsButtonReleased(MouseButton button) { return s_Mouse.IsButtonReleased(button); }

		static float GetMouseX() { return s_Mouse.GetX(); }
		static float GetMouseY() { return s_Mouse.GetY(); }
		static float GetMouseDx() { return s_Mouse.GetDx(); }
		static float GetMouseDy() { return s_Mouse.GetDy(); }
		static float GetMouseScroll() { return s_Mouse.GetScroll(); }
	private:
		static Keyboard s_Keyboard;
		static Mouse s_Mouse;
	};

}
