#pragma once

#include <glm/glm.hpp>

#include <string>

struct CelestialBody
{
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
		return Name == other.Name && Colour == other.Colour &&
			Position == other.Position && Velocity == other.Velocity &&
			Radius == other.Radius && SurfaceGravity == other.SurfaceGravity &&
			Mass == other.Mass;
	}
	inline bool operator!=(const CelestialBody& other) const { return !(*this == other); }
};
