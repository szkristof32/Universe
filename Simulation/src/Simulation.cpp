#include <UniverseEngine/EntryPoint.h>
#include <UniverseEngine/Core/Base.h>

#include <iostream>

class Simulation : public UE::Application
{
public:
	Simulation()
	{
		std::cout << "Loading simulation...\n";
	}
	~Simulation()
	{
		std::cout << "Finishing simulation...\n";
	}
};

UE::Application* UE::CreateApplication(int argc, char** argv)
{
	return new Simulation();
}
