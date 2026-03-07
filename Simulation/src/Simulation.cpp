#include <UniverseEngine/EntryPoint.h>
#include <UniverseEngine/Core/Base.h>

#include "SimulationLayer.h"

#include <iostream>

class Simulation : public UE::Application
{
public:
	Simulation()
	{
		std::cout << "Loading simulation...\n";
		PushLayer<SimulationLayer>();
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
