#include "pch.h"
#include "Shader.h"

#include "UniverseEngine/Utils/FileUtils.h"

#include <glad/gl.h>

namespace UniverseEngine {

	namespace ShaderUtils {

		static uint32_t ShaderStageToGLStage(ShaderStage stage)
		{
			switch (stage)
			{
				case ShaderStage::Vertex:	return GL_VERTEX_SHADER;
				case ShaderStage::Fragment:	return GL_FRAGMENT_SHADER;
			}

			assert(false);
			return 0;
		}

	}

	Shader::Shader()
	{
		m_Program = glCreateProgram();
	}

	Shader::~Shader()
	{
		for (const auto& shader : m_Stages)
		{
			glDetachShader(m_Program, shader);
			glDeleteShader(shader);
		}

		glDeleteProgram(m_Program);
	}

	void Shader::Bind()
	{
		glUseProgram(m_Program);
	}

	void Shader::AttachStage(ShaderStage stage, const std::string& source)
	{
		const char* sourceStr = source.c_str();
		int32_t length = (int32_t)source.size();

		uint32_t shader = glCreateShader(ShaderUtils::ShaderStageToGLStage(stage));
		m_Stages.emplace_back(shader);
		glShaderSource(shader, 1, &sourceStr, &length);
		glCompileShader(shader);
		glAttachShader(m_Program, shader);
		glLinkProgram(m_Program);
	}

	void Shader::LoadFromDisk(const std::string& name)
	{
		static std::string shaderFolder = "Resources/Shaders/";
		std::string vertexPath = shaderFolder + name + ".vert";
		std::string fragmentPath = shaderFolder + name + ".frag";

		AttachStage(ShaderStage::Vertex, FileUtils::ReadFile(vertexPath));
		AttachStage(ShaderStage::Fragment, FileUtils::ReadFile(fragmentPath));
	}

}
