#pragma once

#include <cstddef>
#include <cstdint>

namespace UniverseEngine {

	constexpr inline uint32_t Bitfield(uint32_t x)
	{
		return 1 << x;
	}

	template<typename _Ty, typename... _Args>
	constexpr std::unique_ptr<_Ty> MakeUnique(_Args&&... args)
	{
		return std::unique_ptr<_Ty>(new _Ty(std::forward<_Args>(args)...));
	}

}

namespace UE = UniverseEngine;
