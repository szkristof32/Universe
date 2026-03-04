#pragma once

namespace UniverseEngine {

	struct Buffer
	{
		void* Data;
		size_t Size;

		Buffer(void* data, size_t size) : Data(data), Size(size) {}
		Buffer(size_t size) : Data(nullptr), Size(size) {}
	};

}
