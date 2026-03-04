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

		s_Shader = MakeUnique<Shader>();
		s_Shader->LoadFromDisk("BasicShader");
	}

	Renderer::~Renderer()
	{
		s_Shader.reset();
		s_VertexBuffer.reset();
		s_VertexArray.reset();
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
