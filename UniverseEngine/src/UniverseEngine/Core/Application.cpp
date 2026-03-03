#include "pch.h"
#include "Application.h"

namespace UniverseEngine {

	static Application* s_Application = nullptr;

	Application::Application()
	{
		assert(!s_Application && "You can only create one Application instance!");
		s_Application = this;

		m_Window = std::make_unique<Window>(1280, 720, "UniverseEngine");
		m_Renderer = std::make_unique<Renderer>();
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Initialise();

		while (m_Running)
		{
			m_Window->Update();

			m_Renderer->BeginFrame();
			m_Renderer->EndFrame();
		}

		Shutdown();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(UE_BIND_EVENT_FN(Application::OnWindowClose));
	}

	void Application::Initialise()
	{
		m_Running = true;
	}

	void Application::Shutdown()
	{
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	Reference<Application> Application::Get()
	{
		return s_Application;
	}

}
