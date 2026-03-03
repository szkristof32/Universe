#pragma once

namespace UniverseEngine {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		void Initialise();
		void Shutdown();
	private:
		bool m_Running = false;
	};

	Application* CreateApplication(int argc, char** argv);

}
