#include "pch.h"
#include "Input.h"

namespace UniverseEngine {

	Keyboard Input::s_Keyboard;
	Mouse Input::s_Mouse;

	void Input::Update()
	{
		s_Keyboard.Update();
		s_Mouse.Update();
	}

	void Input::OnEvent(Event& e)
	{
		s_Keyboard.OnEvent(e);
		s_Mouse.OnEvent(e);
	}

}
