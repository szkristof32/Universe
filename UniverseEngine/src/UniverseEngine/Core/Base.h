#pragma once

#include <cstddef>
#include <cstdint>

namespace UniverseEngine {

	constexpr inline uint32_t Bitfield(uint32_t x)
	{
		return 1 << x;
	}

}

namespace UE = UniverseEngine;
