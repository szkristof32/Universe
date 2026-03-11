#pragma once

#include <glm/glm.hpp>

struct CelestialBody
{
	std::string Name = "Planet";

	glm::vec4 Colour;
	glm::vec3 Position;
	glm::vec3 Velocity;
	
	float Radius = 0.0f;
	float SurfaceGravity = 0.0f;
	float Mass = 0.0f;
};
