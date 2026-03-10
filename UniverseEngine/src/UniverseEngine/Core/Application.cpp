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

		m_ImGuiLayer = PushOverlay<ImGuiLayer>();
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Initialise();

		while (m_Running)
		{
			float currentTime = Time::GetTime();
			Timestep delta = currentTime - m_PrevFrameTime;
			m_PrevFrameTime = currentTime;

			m_Window->Update();

			UpdateLayerStack();

			for (auto it = m_LayerStack.rbegin();it!=m_LayerStack.rend();it++)
				(*it)->OnUpdate(delta);

			m_Renderer->BeginFrame();

			for (const auto& layer : m_LayerStack)
				layer->OnRender();

			m_ImGuiLayer->BeginFrame();
			for (const auto& layer : m_LayerStack)
				layer->OnUIRender();
			m_ImGuiLayer->EndFrame();

			m_Renderer->EndFrame();
		}

		Shutdown();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(UE_BIND_EVENT_FN(Application::OnWindowClose));

		if (e.Handled)
			return;

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++)
		{
			if (e.Handled)
				return;
			
			(*it)->OnEvent(e);
		}
	}

	void Application::Initialise()
	{
		UpdateLayerStack();

		m_PrevFrameTime = Time::GetTime();
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
