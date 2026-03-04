#include "pch.h"
#include "Renderer.h"

#include "UniverseEngine/Renderer/RendererAPI.h"

// TODO: temp
#include "Buffers.h"
#include "VertexArray.h"
#include "Shader.h"

namespace UniverseEngine {

	static std::unique_ptr<VertexBuffer> s_VertexBuffer;
	static std::unique_ptr<VertexArray> s_VertexArray;
	static std::unique_ptr<Shader> s_Shader;

	Renderer::Renderer()
	{
		m_Context = MakeUnique<Context>();

		s_VertexArray = MakeUnique<VertexArray>();

		float vertices[] = {
			-0.5f, 0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			0.5f, -0.5f, 0.5f
		};
		s_VertexBuffer = MakeUnique<VertexBuffer>(Buffer(vertices, sizeof(vertices)));
		s_VertexBuffer->Bind();

		s_VertexArray->AddAttribute(AttributeType::Float3);
		s_VertexArray->BakeLayout();

		std::string vertexSource = R"(
			#version 460 core

			layout (location = 0) in vec3 in_position;

			void main()
			{
				gl_Position = vec4(in_position, 1.0);
			}
		)";
		std::string fragmentSource = R"(
			#version 460 core

			layout (location = 0) out vec4 out_colour;

			void main()
			{
				out_colour = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		s_Shader = MakeUnique<Shader>();
		s_Shader->AttachStage(ShaderStage::Vertex, vertexSource);
		s_Shader->AttachStage(ShaderStage::Fragment, fragmentSource);
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::BeginFrame()
	{
		m_Context->BeginFrame();

		s_Shader->Bind();
		s_VertexArray->Bind();
		s_VertexBuffer->Bind();
		RendererAPI::Draw(4);
	}

	void Renderer::EndFrame()
	{
		m_Context->EndFrame();
	}

}
