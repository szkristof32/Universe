#pragma once

#include <UniverseEngine.h>
#include <glm/glm.hpp>

class CameraController
{
public:
	CameraController();

	void Update(UE::Timestep delta);

	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
private:
	glm::vec3 CalculatePosition() const;

	void UpdateViewMatrix();
private:
	glm::mat4 m_ViewMatrix;

	glm::vec3 m_Center;
	glm::vec3 m_Position;

	float m_Theta = 0.0f;
	float m_Pitch = 30.0f;
	float m_Distance = 10.0f;

	bool m_ValuesChanged = true;
};
