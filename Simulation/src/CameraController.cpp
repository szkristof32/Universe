#include "CameraController.h"

#include <memtrace.h>

#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

using namespace UniverseEngine;

CameraController::CameraController()
	: m_Center(glm::vec3(0.0f), 10.0f), m_Position(CalculatePosition())
{
	m_Pitch.SetAgility(10.0f);
	m_Theta.SetAgility(10.0f);
	m_Distance.SetAgility(5.0f);
}

void CameraController::Update(Timestep delta, bool enabled)
{
	if (enabled)
	{
		if (Input::IsButtonDown(MouseButton::Left))
		{
			float dx = Input::GetMouseDx() * m_HorizontalRotationSpeed * delta;
			float dy = Input::GetMouseDy() * m_VerticalRotationSpeed * delta;

			m_Theta.IncreaseTarget(-dx);
			m_Pitch.IncreaseTarget(dy);

			if (m_Pitch.GetTarget() >= 85.0f)
				m_Pitch.SetTarget(85.0f);
			if (m_Pitch.GetTarget() <= -85.0f)
				m_Pitch.SetTarget(-85.0f);
		}
		if (Input::GetMouseScroll() != 0)
		{
			float zoomChange = Input::GetMouseScroll() * m_ZoomSpeed * delta;

			m_Distance.IncreaseTarget(-zoomChange);
		}
	}

	m_Center.Update(delta);
	m_Pitch.Update(delta);
	m_Theta.Update(delta);
	m_Distance.Update(delta);

	m_Position = CalculatePosition();

	UpdateViewMatrix();
}

void CameraController::OnUIRender()
{
	ImGui::Begin("Camera controller");

	ImGui::DragFloat("Horizontal rotation speed", &m_HorizontalRotationSpeed, 0.01f, 0.0f, 100.0f);
	ImGui::DragFloat("Vertical rotation speed", &m_VerticalRotationSpeed, 0.01f, 0.0f, 100.0f);
	ImGui::DragFloat("Zoom speed", &m_ZoomSpeed, 0.01f, 0.0f, 100.0f);

	ImGui::DragFloat("Horizontal rotation agility", &m_Theta.GetAgility(), 0.01f, 0.0f, 100.0f);
	ImGui::DragFloat("Vertical rotation agility", &m_Pitch.GetAgility(), 0.01f, 0.0f, 100.0f);
	ImGui::DragFloat("Zoom agility", &m_Distance.GetAgility(), 0.01f, 0.0f, 100.0f);

	ImGui::End();
}

glm::vec3 CameraController::CalculatePosition() const
{
	float verticalOffset = m_Distance.Get() * glm::sin(glm::radians(glm::mod(m_Pitch.Get(), 360.0f)));
	float horizontalOffset = m_Distance.Get() * glm::cos(glm::radians(glm::mod(m_Pitch.Get(), 360.0f)));

	float xOffset = horizontalOffset * glm::sin(glm::radians(glm::mod(m_Theta.Get(), 360.0f)));
	float zOffset = horizontalOffset * glm::cos(glm::radians(glm::mod(m_Theta.Get(), 360.0f)));

	return glm::vec3(xOffset, verticalOffset, zOffset);
}

void CameraController::UpdateViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_Position, m_Center.Get(), glm::vec3(0.0f, 1.0f, 0.0f));
}

