#include "SimulationLayer.h"

#include <iostream>

void SimulationLayer::OnAttach()
{
	std::cout << "Simulation layer attached!\n";
}

void SimulationLayer::OnDetach()
{
	std::cout << "Simulation layer detached!\n";
}
