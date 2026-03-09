#pragma once

#include "UniverseEngine/Core/Window.h"
#include "UniverseEngine/Core/LayerStack.h"
#include "UniverseEngine/Core/ImGuiLayer.h"

#include "UniverseEngine/Renderer/Renderer.h"

#include "UniverseEngine/Core/Events/ApplicationEvents.h"

#include <memory>

namespace UniverseEngine {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		template<typename _Ty, typename... _Args>
		Reference<_Ty> PushLayer(_Args&&... args)
		{
			std::unique_ptr<_Ty> layer = MakeUnique<_Ty>(std::forward<_Args>(args)...);
			Reference<_Ty> ref = layer;
			m_LayersToPush.emplace_back(std::move(layer));
			return ref;
		}
		template<typename _Ty, typename... _Args>
		Reference<_Ty> PushOverlay(_Args&&... args)
		{
			std::unique_ptr<_Ty> overlay = MakeUnique<_Ty>(std::forward<_Args>(args)...);
			Reference<_Ty> ref = overlay;
			m_OverlaysToPush.emplace_back(std::move(overlay));
			return ref;
		}
		void PopLayer(Reference<Layer> layer)
		{
			m_LayersToPop.emplace_back(layer);
		}
		void PopOverlay(Reference<Layer> overlay)
		{
			m_OverlaysToPop.emplace_back(overlay);
		}

		static Reference<Application> Get();

		Reference<Window> GetWindow() const { return m_Window; }
	private:
		void Initialise();
		void Shutdown();
		void UpdateLayerStack();

		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> m_Renderer;

		LayerStack m_LayerStack;
		std::vector<std::unique_ptr<Layer>> m_LayersToPush;
		std::vector<std::unique_ptr<Layer>> m_OverlaysToPush;
		std::vector<Reference<Layer>> m_LayersToPop;
		std::vector<Reference<Layer>> m_OverlaysToPop;

		Reference<ImGuiLayer> m_ImGuiLayer;

		bool m_Running = false;
	};

	Application* CreateApplication(int argc, char** argv);

}
