#include "pch.h"
#include "Core.h"

namespace UniverseEngine {

	struct CoreData
	{
	};

	CoreData* Core::s_Data = nullptr;

	void Core::Initialise()
	{
		s_Data = new CoreData;

		std::cout << "Initialising Core...\n";
	}

	void Core::Shutdown()
	{
		std::cout << "Shutting down Core...\n";

		delete s_Data;
	}

}
