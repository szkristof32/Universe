#include "SimulationLayer.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

using namespace UniverseEngine;

void SimulationLayer::OnAttach()
{
	std::vector<Vertex> vertices = {
		{
			{ -0.5f, 0.5f, 0.0f },
			{ 0.0f, 0.0f, -1.0f },
		},
		{
			{ -0.5f, -0.5f, 0.0f },
			{ 0.0f, 0.0f, -1.0f },
		},
		{
			{ 0.5f, 0.5f, 0.0f },
			{ 0.0f, 0.0f, -1.0f },
		},
		{
			{ 0.5f, 0.5f, 0.0f },
			{ 0.0f, 0.0f, -1.0f },
		},
		{
			{ -0.5f, -0.5f, 0.0f },
			{ 0.0f, 0.0f, -1.0f },
		},
		{
			{ 0.5f, -0.5f, 0.0f },
			{ 0.0f, 0.0f, -1.0f },
		},
	};

	m_PlanetMesh = Mesh(vertices);

	m_Shader = MakeUnique<Shader>();
	m_Shader->LoadFromDisk("PlanetShader");

	m_Camera.ProjectionView = glm::perspectiveFov(glm::radians(70.0f), 16.0f / 9.0f, 1.0f, 0.1f, 100.0f)
		* glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, -4.0f });
	m_CameraUniformBuffer = MakeUnique<UniformBuffer>(Buffer(&m_Camera, sizeof(m_Camera)));
	m_CameraUniformBuffer->BindToShader(0);

	m_Properties.Transformation = glm::mat4(1.0f);
	m_Properties.Colour = glm::vec4(0.8f, 0.2f, 0.3f, 1.0f);
	m_PropertiesUniformBuffer = MakeUnique<UniformBuffer>(Buffer(&m_Properties, sizeof(m_Properties)));
	m_PropertiesUniformBuffer->BindToShader(1);

	CelestialBody testBody{};
	testBody.Position = glm::vec3(0.0f);
	testBody.Colour = { 0.2f, 0.4f, 0.6f, 1.0f };
	testBody.Radius = 1.5f;
	m_Bodies.emplace_back(std::move(testBody));
}

void SimulationLayer::OnDetach()
{
}

void SimulationLayer::OnUpdate(float ts)
{
}

void SimulationLayer::OnRender()
{
	if (m_Bodies.empty())
		return;

	m_Shader->Bind();
	m_CameraUniformBuffer->Bind();
	m_PropertiesUniformBuffer->Bind();

	m_PlanetMesh.GetVertexArray()->Bind();
	m_PlanetMesh.GetVertexBuffer()->Bind();
	m_PlanetMesh.GetIndexBuffer()->Bind();

	for (const auto& body : m_Bodies)
	{
		m_Properties.Transformation = glm::translate(glm::mat4(1.0f), body.Position) *
			glm::scale(glm::mat4(1.0f), glm::vec3(body.Radius));
		m_Properties.Colour = body.Colour;
		m_PropertiesUniformBuffer->SetData(Buffer(&m_Properties, sizeof(m_Properties)));
	
		RendererAPI::DrawIndexed(6, PrimitiveMode::TriangleList);
	}
}
