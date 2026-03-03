#pragma once

namespace UniverseEngine {

	class Core
	{
	public:
		static void Initialise();
		static void Shutdown();
	private:
		static struct CoreData* s_Data;
	};

}
