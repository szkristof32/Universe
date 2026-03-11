#pragma once

#include <UniverseEngine.h>

#include "CelestialBody.h"
#include "MeshGenerator.h"
#include "CameraController.h"

#include "Panels/PropertiesPanel.h"
#include "Panels/BodiesPanel.h"

class SimulationLayer : public UE::Layer
{
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(UE::Timestep delta) override;
	virtual void OnRender() override;
	virtual void OnUIRender() override;
private:
	void RecalculateProjection(float aspectRatio);
private:
	MeshGenerator m_MeshGenerator;
	UE::Mesh m_PlanetMesh;
	CameraController m_CameraController;

	bool m_ViewportFocused = false;
	glm::vec2 m_ViewportSize;
	uint32_t m_ViewportSizeGeneration = 0;
	uint32_t m_PrevViewportSizeGeneration = 0;

	std::unique_ptr<UE::Framebuffer> m_Framebuffer;
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
	CelestialBody m_BodyToAdd{};
	bool m_Adding = false;

	std::unique_ptr<PropertiesPanel> m_PropertiesPanel;
	std::unique_ptr<BodiesPanel> m_BodiesPanel;
};
