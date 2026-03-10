#include "pch.h"
#include "Keyboard.h"

namespace UniverseEngine {

	void Keyboard::Update()
	{
		m_KeysPressedThisFrame.clear();
		m_KeysReleasedThisFrame.clear();
		m_KeysRepeatedThisFrame.clear();
		m_KeysTypedThisFrame.clear();
	}

	void Keyboard::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressEvent>(UE_BIND_EVENT_FN(Keyboard::OnKeyPress));
		dispatcher.Dispatch<KeyReleaseEvent>(UE_BIND_EVENT_FN(Keyboard::OnKeyRelease));
		dispatcher.Dispatch<KeyTypeEvent>(UE_BIND_EVENT_FN(Keyboard::OnKeyTyped));
	}

	bool Keyboard::OnKeyPress(KeyPressEvent& e)
	{
		m_KeysDown.emplace((Key)e.GetKeyCode());
		m_KeysPressedThisFrame.emplace((Key)e.GetKeyCode());

		if (e.DoesRepeat())
			m_KeysRepeatedThisFrame.emplace((Key)e.GetKeyCode());

		return false;
	}

	bool Keyboard::OnKeyRelease(KeyReleaseEvent& e)
	{
		m_KeysDown.erase((Key)e.GetKeyCode());
		m_KeysReleasedThisFrame.emplace((Key)e.GetKeyCode());

		return false;
	}

	bool Keyboard::OnKeyTyped(KeyTypeEvent& e)
	{
		m_KeysTypedThisFrame.emplace_back((Key)e.GetScancode());

		return false;
	}

}
