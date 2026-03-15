#include "SimulationLayer.h"

#include <memtrace.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/norm.hpp>

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <iostream>

using namespace UniverseEngine;

void SimulationLayer::OnAttach()
{
	m_Camera.Projection = glm::perspectiveFov(glm::radians(70.0f), 16.0f / 9.0f, 1.0f, 0.1f, 100.0f);
	m_Camera.View = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, -4.0f });

	CelestialBody testBody{};
	testBody.Name = "Test body";
	testBody.Position = glm::vec3(0.0f);
	testBody.Colour = { 0.2f, 0.4f, 0.6f, 1.0f };
	testBody.Radius = 1.5f;
	testBody.SurfaceGravity = 300.0f;
	testBody.CalculateMass();
	m_Bodies.emplace_back(std::move(testBody));

	m_PropertiesPanel = MakeUnique<PropertiesPanel>();
	m_BodiesPanel = MakeUnique<BodiesPanel>();

	m_PropertiesPanel->SetDeleteCallback([&](CelestialBody& body)
	{
		auto it = std::find(m_Bodies.begin(), m_Bodies.end(), body);
		if (it != m_Bodies.end())
			m_Bodies.erase(it);
	});
	m_BodiesPanel->SetSelectBodyCallback([&](CelestialBody& body)
	{
		m_PropertiesPanel->SetSelectedBody(body);
	});
	m_BodiesPanel->SetDeselectBodyCallback([&]()
	{
		m_PropertiesPanel->ClearSelectedBody();
	});
	m_BodiesPanel->SetBodies(m_Bodies);
}

void SimulationLayer::OnDetach()
{
}

void SimulationLayer::OnUpdate(Timestep delta)
{
	m_CameraController.Update(delta, m_ViewportFocused);

	if (m_CameraController.GetViewMatrix() != m_Camera.View)
		m_Camera.View = m_CameraController.GetViewMatrix();

	if (m_EnableSimulation)
	{
		for (auto& body : m_Bodies)
		{
			UpdateVelocity(body, delta);
		}
		for (auto& body : m_Bodies)
		{
			UpdatePosition(body, delta);
		}
	}
}

void SimulationLayer::OnRender()
{
	if (m_Bodies.empty())
		return;

	m_Renderer.BeginFrame(m_Camera, m_ViewportSize);

	for (const auto& body : m_Bodies)
	{
		m_Renderer.DrawPlanet(body);
	}

	m_Renderer.EndFrame();
}

void SimulationLayer::OnUIRender()
{
	ImGui::DockSpaceOverViewport();

	m_CameraController.OnUIRender();

	m_PropertiesPanel->OnUIRender();
	m_BodiesPanel->OnUIRender();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
	ImGui::Begin("Viewport");
	ImGui::PopStyleVar();

	m_ViewportFocused = ImGui::IsWindowHovered();

	ImVec2 contentRegion = ImGui::GetContentRegionAvail();
	if (*reinterpret_cast<glm::vec2*>(&contentRegion) != m_ViewportSize)
	{
		m_ViewportSize = { contentRegion.x, contentRegion.y };
		RecalculateProjection(contentRegion.x / contentRegion.y);
	}

	ImGui::Image(m_Renderer.GetFinalImage(), contentRegion, { 0, 1 }, { 1, 0 });

	ImGui::End();

	ImGui::Begin("Settings");

	ImGui::Checkbox("Enable simulation", &m_EnableSimulation);
	ImGui::DragFloat("Gravitational constant", &m_GravitationalConstant, 0.0001f, 0.0f, 0.0f, "%.4f");

	ImGui::End();
}

void SimulationLayer::RecalculateProjection(float aspectRatio)
{
	m_Camera.Projection = glm::perspectiveFov(glm::radians(70.0f), aspectRatio, 1.0f, 0.1f, 1000.0f);
}

void SimulationLayer::UpdateVelocity(CelestialBody& body, Timestep delta)
{
	for (const auto& other : m_Bodies)
	{
		if (body == other)
			continue;

		float distance2 = glm::distance2(body.Position, other.Position);
		glm::vec3 forceDirection = glm::normalize(other.Position - body.Position);

		glm::vec3 acceleration = forceDirection * m_GravitationalConstant * body.Mass * other.Mass / distance2;
		body.Velocity += acceleration * (float)delta;
	}
}

void SimulationLayer::UpdatePosition(CelestialBody& body, Timestep delta)
{
	body.Position += body.Velocity * (float)delta;
}
