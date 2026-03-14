#pragma once

#include <UniverseEngine.h>
#include <glm/glm.hpp>

class CameraController
{
public:
	CameraController();

	void Update(UE::Timestep delta, bool enabled);

	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

	void OnUIRender();
private:
	glm::vec3 CalculatePosition() const;

	void UpdateViewMatrix();
private:
	glm::mat4 m_ViewMatrix;

	UE::SmoothValue<glm::vec3> m_Center;
	glm::vec3 m_Position;

	UE::SmoothValue<float> m_Theta = 0.0f;
	UE::SmoothValue<float> m_Pitch = 30.0f;
	UE::SmoothValue<float> m_Distance = 10.0f;

	float m_HorizontalRotationSpeed = 15.0f;
	float m_VerticalRotationSpeed = 30.0f;
	float m_ZoomSpeed = 40.0f;
};
