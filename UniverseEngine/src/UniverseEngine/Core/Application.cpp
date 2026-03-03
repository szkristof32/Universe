#include "pch.h"
#include "Application.h"

namespace UniverseEngine {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Initialise();

		while (m_Running)
		{
			m_Running = false;
		}

		Shutdown();
	}

	void Application::Initialise()
	{
		m_Running = true;
	}

	void Application::Shutdown()
	{
	}

}
