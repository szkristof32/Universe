#pragma once

#include <UniverseEngine.h>

#include <glm/glm.hpp>

#include <string>

struct CelestialBody
{
	UE::UUID ID{};

	std::string Name = "Planet";

	glm::vec4 Colour;
	glm::vec3 Position;
	glm::vec3 Velocity;

	float Radius = 0.0f;
	float SurfaceGravity = 0.0f;
	float Mass = 0.0f;

	bool Active = false;

	void CalculateMass() { Mass = SurfaceGravity * Radius * Radius; }

	inline bool operator==(const CelestialBody& other) const
	{
		return ID == other.ID;
	}
	inline bool operator!=(const CelestialBody& other) const { return !(*this == other); }
};
