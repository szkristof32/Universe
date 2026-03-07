#include "SimulationLayer.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

using namespace UniverseEngine;

void SimulationLayer::OnAttach()
{
	m_VertexArray = MakeUnique<VertexArray>();

	float vertices[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	m_VertexBuffer = MakeUnique<VertexBuffer>(Buffer(vertices, sizeof(vertices)));
	m_VertexBuffer->Bind();

	m_VertexArray->AddAttribute(AttributeType::Float3);
	m_VertexArray->BakeLayout();

	uint32_t indices[] = {
		0, 1, 2,
		2, 1, 3
	};
	m_IndexBuffer = MakeUnique<IndexBuffer>(Buffer(indices, sizeof(indices)));

	m_Shader = MakeUnique<Shader>();
	m_Shader->LoadFromDisk("BasicShader");

	m_Matrices.ProjectionView = glm::perspectiveFov(glm::radians(70.0f), 16.0f / 9.0f, 1.0f, 0.1f, 100.0f)
		* glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, -4.0f });
	m_Matrices.Transformation = glm::mat4(1.0f);
	m_MatricesUniformBuffer = MakeUnique<UniformBuffer>(Buffer(&m_Matrices, sizeof(m_Matrices)));
	m_MatricesUniformBuffer->BindToShader(0);

	m_Properties.Colour = glm::vec4(0.8f, 0.2f, 0.3f, 1.0f);
	m_PropertiesUniformBuffer = MakeUnique<UniformBuffer>(Buffer(&m_Properties, sizeof(m_Properties)));
	m_PropertiesUniformBuffer->BindToShader(1);
}

void SimulationLayer::OnDetach()
{
}

void SimulationLayer::OnRender()
{
	m_Matrices.Transformation = glm::rotate(m_Matrices.Transformation, glm::radians(3.0f), { -0.7f, 1.0f, 0.3f });
	m_MatricesUniformBuffer->SetData(Buffer(&m_Matrices, sizeof(m_Matrices)));

	m_Shader->Bind();
	m_MatricesUniformBuffer->Bind();
	m_PropertiesUniformBuffer->Bind();

	m_VertexArray->Bind();
	m_VertexBuffer->Bind();
	m_IndexBuffer->Bind();

	RendererAPI::DrawIndexed(6, PrimitiveMode::TriangleList);
}
