#pragma once

#include <chrono>

namespace UniverseEngine {

	class Timer
	{
	public:
		Timer() { Reset(); }

		inline void Reset() { m_StartTime = std::chrono::high_resolution_clock::now(); }

		inline float Elapsed() const
		{ 
			return std::chrono::duration_cast<std::chrono::microseconds>(
				std::chrono::high_resolution_clock::now() - m_StartTime
			).count() * 0.001f * 0.001f;
		}
		inline float ElapsedMillis() const
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(
				std::chrono::high_resolution_clock::now() - m_StartTime
			).count() * 0.001f;
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
	};

	class ScopedTimer : public Timer
	{
	public:
		ScopedTimer(const std::string& name)
			: m_Name(name)
		{
		}
		~ScopedTimer()
		{
			float time = ElapsedMillis();
			std::cout << "[Timer] " << m_Name << " - " << time << "ms\n";
		}
	private:
		std::string m_Name;
	};

}
