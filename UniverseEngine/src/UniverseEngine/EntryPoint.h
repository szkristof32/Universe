#pragma once

#include "UniverseEngine/Core/Core.h"
#include "UniverseEngine/Core/Application.h"

namespace UniverseEngine {

	extern Application* CreateApplication(int argc, char** argv);

	int Main(int argc, char** argv)
	{
		Core::Initialise();
		auto app = CreateApplication(argc, argv);
		app->Run();
		delete app;
		Core::Shutdown();
		return 0;
	}

}

#if UE_PLATFORM_WINDOWS && UE_RELEASE

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	(void)hInstance;
	(void)hPrevInstance;
	(void)lpCmdLine;
	(void)nShowCmd;
	return UniverseEngine::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return UniverseEngine::Main(argc, argv);
}

#endif
