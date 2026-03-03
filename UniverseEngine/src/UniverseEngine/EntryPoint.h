#pragma once

#include "pch.h"
#include "UniverseEngine/Core/Core.h"

namespace UniverseEngine {

	int Main(int argc, char** argv)
	{
		Core::Initialise();
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
