#pragma once

#include <UniverseEngine/Core/Layer.h>

#include <iostream>

class SimulationLayer : public UE::Layer
{
public:
	SimulationLayer()
	{
		std::cout << "Create\n";
	}
	~SimulationLayer()
	{
		std::cout << "Destroy\n";
	}

	virtual void OnAttach() override;
	virtual void OnDetach() override;
};
