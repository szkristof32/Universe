#include "CameraController.h"

#include <memtrace.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace UniverseEngine;

CameraController::CameraController()
	: m_Center(0.0f), m_Position(CalculatePosition())
{
}

void CameraController::Update(Timestep delta)
{
	m_Theta += 30.0f * delta;
	m_Center.y = 1.2f * glm::sin(glm::radians(m_Theta));
	m_ValuesChanged = true;

	m_Position = CalculatePosition();

	if (m_ValuesChanged)
	{
		UpdateViewMatrix();
		m_ValuesChanged = false;
	}
}

glm::vec3 CameraController::CalculatePosition() const
{
	float verticalOffset = m_Distance * glm::sin(glm::radians(m_Pitch));
	float horizontalOffset = m_Distance * glm::cos(glm::radians(m_Pitch));

	float xOffset = horizontalOffset * glm::sin(glm::radians(m_Theta));
	float zOffset = horizontalOffset * glm::cos(glm::radians(m_Theta));

	return glm::vec3(xOffset, verticalOffset, zOffset);
}

void CameraController::UpdateViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_Position, m_Center, { 0.0f, 1.0f, 0.0f });
}

