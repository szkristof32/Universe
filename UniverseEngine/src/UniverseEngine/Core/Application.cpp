#include "pch.h"
#include "Application.h"

namespace UniverseEngine {

	static Application* s_Application = nullptr;

	Application::Application()
	{
		assert(!s_Application && "You can only create one Application instance!");
		s_Application = this;

		m_Window = MakeUnique<Window>(1280, 720, "UniverseEngine");
		m_Renderer = MakeUnique<Renderer>();
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

			UpdateLayerStack();

			for (const auto& layer : m_LayerStack)
				layer->OnUpdate(0);

			m_Renderer->BeginFrame();

			for (const auto& layer : m_LayerStack)
				layer->OnRender();

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
		UpdateLayerStack();

		m_Running = true;
	}

	void Application::Shutdown()
	{
		m_LayerStack.PopAll();
	}

	void Application::UpdateLayerStack()
	{
		for (auto&& overlay : m_OverlaysToPush)
		{
			overlay->OnAttach();
			m_LayerStack.PushOverlay(std::move(overlay));
		}
		for (auto&& layer : m_LayersToPush)
		{
			layer->OnAttach();
			m_LayerStack.PushLayer(std::move(layer));
		}
		for (const auto& layer : m_LayersToPop)
		{
			layer->OnDetach();
			m_LayerStack.PopLayer(layer);
		}
		for (const auto& overlay : m_OverlaysToPop)
		{
			overlay->OnDetach();
			m_LayerStack.PopOverlay(overlay);
		}

		m_LayersToPush.clear();
		m_OverlaysToPush.clear();
		m_LayersToPop.clear();
		m_OverlaysToPop.clear();
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
