#include "SimulationLayer.h"

#include <memtrace.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <iostream>

using namespace UniverseEngine;

void SimulationLayer::OnAttach()
{
	m_PlanetMesh = m_MeshGenerator.GenerateSphere();

	m_Shader = MakeUnique<Shader>();
	m_Shader->LoadFromDisk("PlanetShader");

	m_Camera.Projection = glm::perspectiveFov(glm::radians(70.0f), 16.0f / 9.0f, 1.0f, 0.1f, 100.0f);
	m_Camera.View = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, -4.0f });
	m_CameraUniformBuffer = MakeUnique<UniformBuffer>(Buffer(&m_Camera, sizeof(m_Camera)));
	m_CameraUniformBuffer->BindToShader(0);

	m_Properties.Transformation = glm::mat4(1.0f);
	m_Properties.Colour = glm::vec4(0.8f, 0.2f, 0.3f, 1.0f);
	m_PropertiesUniformBuffer = MakeUnique<UniformBuffer>(Buffer(&m_Properties, sizeof(m_Properties)));
	m_PropertiesUniformBuffer->BindToShader(1);

	CelestialBody testBody{};
	testBody.Name = "Test body";
	testBody.Position = glm::vec3(0.0f);
	testBody.Colour = { 0.2f, 0.4f, 0.6f, 1.0f };
	testBody.Radius = 1.5f;
	m_Bodies.emplace_back(std::move(testBody));
}

void SimulationLayer::OnDetach()
{
}

void SimulationLayer::OnUpdate(Timestep delta)
{
	m_CameraController.Update(delta);

	if (m_CameraController.GetViewMatrix() != m_Camera.View)
	{
		m_Camera.View = m_CameraController.GetViewMatrix();
		m_CameraGeneration++;
	}
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

	if (m_CameraGeneration > m_PrevCameraGeneration)
	{
		m_CameraUniformBuffer->SetData(Buffer(&m_Camera, sizeof(m_Camera)));
		m_PrevCameraGeneration = m_CameraGeneration;
	}

	RendererAPIConfiguration rendererAPIConfig{};
	rendererAPIConfig.EnableDepthTest = true;

	RendererAPI::Configure(rendererAPIConfig);

	for (const auto& body : m_Bodies)
	{
		m_Properties.Transformation = glm::translate(glm::mat4(1.0f), body.Position) *
			glm::scale(glm::mat4(1.0f), glm::vec3(body.Radius));
		m_Properties.Colour = body.Colour;
		m_PropertiesUniformBuffer->SetData(Buffer(&m_Properties, sizeof(m_Properties)));

		RendererAPI::DrawIndexed(m_PlanetMesh.GetIndexCount(), PrimitiveMode::TriangleList);
	}

	if (m_Adding)
	{
		m_Properties.Transformation = glm::translate(glm::mat4(1.0f), m_BodyToAdd.Position) *
			glm::scale(glm::mat4(1.0f), glm::vec3(m_BodyToAdd.Radius));
		m_Properties.Colour = m_BodyToAdd.Colour;
		m_PropertiesUniformBuffer->SetData(Buffer(&m_Properties, sizeof(m_Properties)));

		RendererAPI::DrawIndexed(m_PlanetMesh.GetIndexCount(), PrimitiveMode::TriangleList);
	}
}

void SimulationLayer::OnUIRender()
{
	m_CameraController.OnUIRender();

	ImGui::Begin("Bodies");

	ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen;

	if (ImGui::TreeNodeEx("Bodies", treeNodeFlags))
	{
		treeNodeFlags |= ImGuiTreeNodeFlags_Leaf;

		for (size_t i = 0; i < m_Bodies.size(); i++)
		{
			const auto& body = m_Bodies[i];

			if (ImGui::TreeNodeEx(body.Name.c_str(), treeNodeFlags | (m_SelectedBody == i ? ImGuiTreeNodeFlags_Selected : 0)))
				ImGui::TreePop();

			if (ImGui::IsItemClicked() || ImGui::IsItemFocused())
				m_SelectedBody = i;
		}

		ImGui::TreePop();
	}

	if (ImGui::Button("Add body"))
	{
		ImGui::OpenPopup("Add body");
		m_BodyToAdd = {};
		m_Adding = true;
	}

	if (ImGui::BeginPopupModal("Add body", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::InputText("Name", &m_BodyToAdd.Name);
		ImGui::ColorEdit4("Colour", glm::value_ptr(m_BodyToAdd.Colour));
		ImGui::DragFloat3("Position", glm::value_ptr(m_BodyToAdd.Position), 0.01f);
		ImGui::DragFloat3("Velocity", glm::value_ptr(m_BodyToAdd.Velocity), 0.01f);
		ImGui::DragFloat("Radius", &m_BodyToAdd.Radius, 0.01f, 0.1f);
		ImGui::DragFloat("Surface gravity", &m_BodyToAdd.SurfaceGravity, 0.01f);

		if (ImGui::Button("Add"))
		{
			m_Bodies.emplace_back(std::move(m_BodyToAdd));
			m_BodyToAdd = {};
			m_Adding = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine(0.0f, 10.0f);
		if (ImGui::Button("Close"))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	ImGui::End();

	ImGui::Begin("Properties");

	if (m_SelectedBody == -1 || m_SelectedBody >= m_Bodies.size())
	{
		ImGui::Text("Select a body to see its properties");
	}
	else
	{
		auto& body = m_Bodies[m_SelectedBody];

		ImGui::InputText("Name", &body.Name);
		ImGui::ColorEdit4("Colour", glm::value_ptr(body.Colour));
		ImGui::DragFloat3("Position", glm::value_ptr(body.Position), 0.01f);
		ImGui::DragFloat3("Velocity", glm::value_ptr(body.Velocity), 0.01f);
		ImGui::DragFloat("Radius", &body.Radius, 0.01f, 0.1f);
		ImGui::DragFloat("Surface gravity", &body.SurfaceGravity, 0.01f);

		if (ImGui::Button("Delete"))
		{
			ImGui::OpenPopup("Confirmation");
		}

		if (ImGui::BeginPopupModal("Confirmation", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Are you sure you want to delete the body?");

			if (ImGui::Button("Yes"))
			{
				m_Bodies.erase(m_Bodies.begin() + m_SelectedBody);
				m_SelectedBody = -1;
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

	ImGui::End();
}

void SimulationLayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(SimulationLayer::OnWindowResize));
}

bool SimulationLayer::OnWindowResize(WindowResizeEvent& e)
{
	float aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	m_Camera.Projection = glm::perspectiveFov(glm::radians(70.0f), aspectRatio, 1.0f, 0.1f, 1000.0f);
	m_CameraGeneration++;
	return false;
}
