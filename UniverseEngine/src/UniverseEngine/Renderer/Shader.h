#pragma once

namespace UniverseEngine {

	enum class ShaderStage
	{
		None = 0,
		Vertex = Bitfield(0),
		Fragment = Bitfield(1)
	};

	class Shader
	{
	public:
		Shader();
		~Shader();

		void Bind();

		void AttachStage(ShaderStage stage, const std::string& source);
		void LoadFromDisk(const std::string& name);
	private:
		uint32_t m_Program;
		std::vector<uint32_t> m_Stages;
	};

}
