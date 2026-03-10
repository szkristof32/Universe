#pragma once

#include <UniverseEngine.h>

#include "CelestialBody.h"
#include "MeshGenerator.h"
#include "CameraController.h"

class SimulationLayer : public UE::Layer
{
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(UE::Timestep delta) override;
	virtual void OnRender() override;
	virtual void OnUIRender() override;

	virtual void OnEvent(UE::Event& e) override;
private:
	bool OnWindowResize(UE::WindowResizeEvent& e);
private:
	MeshGenerator m_MeshGenerator;
	UE::Mesh m_PlanetMesh;
	CameraController m_CameraController;

	std::unique_ptr<UE::Shader> m_Shader;
	std::unique_ptr<UE::UniformBuffer> m_CameraUniformBuffer;
	std::unique_ptr<UE::UniformBuffer> m_PropertiesUniformBuffer;
	struct Camera
	{
		glm::mat4 Projection;
		glm::mat4 View;
	};
	Camera m_Camera;
	uint32_t m_CameraGeneration = 0;
	uint32_t m_PrevCameraGeneration = 0;
	struct Properties
	{
		glm::mat4 Transformation;
		glm::vec4 Colour;
	};
	Properties m_Properties;

	std::vector<CelestialBody> m_Bodies;
};
