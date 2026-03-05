#include "pch.h"
#include "Renderer.h"

#include "UniverseEngine/Renderer/RendererAPI.h"

// TODO: temp
#include "Buffers.h"
#include "VertexArray.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace UniverseEngine {

	static std::unique_ptr<VertexBuffer> s_VertexBuffer;
	static std::unique_ptr<VertexArray> s_VertexArray;
	static std::unique_ptr<Shader> s_Shader;
	static std::unique_ptr<UniformBuffer> s_MatricesUniformBuffer;
	static std::unique_ptr<UniformBuffer> s_PropertiesUniformBuffer;

	struct Matrices
	{
		glm::mat4 ProjectionView;
		glm::mat4 Transformation;
	};
	static Matrices s_Matrices;
	struct Properties
	{
		glm::vec4 Colour;
	};
	static Properties s_Properties;

	Renderer::Renderer()
	{
		m_Context = MakeUnique<Context>();

		s_VertexArray = MakeUnique<VertexArray>();

		float vertices[] = {
			-0.5f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			0.5f, -0.5f, 0.0f
		};
		s_VertexBuffer = MakeUnique<VertexBuffer>(Buffer(vertices, sizeof(vertices)));
		s_VertexBuffer->Bind();

		s_VertexArray->AddAttribute(AttributeType::Float3);
		s_VertexArray->BakeLayout();

		s_Shader = MakeUnique<Shader>();
		s_Shader->LoadFromDisk("BasicShader");

		s_Matrices.ProjectionView = glm::perspectiveFov(glm::radians(70.0f), 16.0f / 9.0f, 1.0f, 0.1f, 100.0f)
			* glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, -4.0f });
		s_Matrices.Transformation = glm::mat4(1.0f);
		s_MatricesUniformBuffer = std::make_unique<UniformBuffer>(Buffer(&s_Matrices, sizeof(s_Matrices)));
		s_MatricesUniformBuffer->BindToShader(0);

		s_Properties.Colour = glm::vec4(0.8f, 0.2f, 0.3f, 1.0f);
		s_PropertiesUniformBuffer = std::make_unique<UniformBuffer>(Buffer(&s_Properties, sizeof(s_Properties)));
		s_PropertiesUniformBuffer->BindToShader(1);
	}

	Renderer::~Renderer()
	{
		s_PropertiesUniformBuffer.reset();
		s_MatricesUniformBuffer.reset();
		s_Shader.reset();
		s_VertexBuffer.reset();
		s_VertexArray.reset();
	}

	void Renderer::BeginFrame()
	{
		m_Context->BeginFrame();

		s_Matrices.Transformation = glm::rotate(s_Matrices.Transformation, glm::radians(3.0f), { -0.7f, 1.0f, 0.3f });
		s_MatricesUniformBuffer->SetData(Buffer(&s_Matrices, sizeof(s_Matrices)));

		s_Shader->Bind();
		s_MatricesUniformBuffer->Bind();
		s_PropertiesUniformBuffer->Bind();

		s_VertexArray->Bind();
		s_VertexBuffer->Bind();

		RendererAPI::Draw(4);
	}

	void Renderer::EndFrame()
	{
		m_Context->EndFrame();
	}

}
