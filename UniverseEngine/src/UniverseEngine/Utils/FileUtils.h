#pragma once

#include <fstream>

namespace UniverseEngine {
	
	namespace FileUtils {

		template<typename _Ty = std::string>
		inline _Ty ReadFile(const std::string& path, bool binary = false)
		{
			std::ifstream file(path, std::ios::ate | (binary ? std::ios::binary : (std::ios_base::openmode)0));
			assert(file && "Failed to open file!");

			size_t fileSize = file.tellg();
			file.seekg(0, std::ios::beg);

			_Ty buffer;
			buffer.resize(fileSize / sizeof(typename _Ty::value_type));
			file.read(&buffer[0], fileSize);

			return buffer;
		}

	}

}
