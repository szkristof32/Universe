#pragma once

namespace UniverseEngine {

	class Timestep
	{
	public:
		Timestep() = default;
		Timestep(float timestep) : m_Timestep(timestep) {}

		inline float GetSeconds() const { return m_Timestep; }
		inline float GetMilliseconds() const { return m_Timestep * 1000.0f; }

		inline operator float() const { return GetSeconds(); }
	private:
		float m_Timestep = 0.0f;
	};

}
