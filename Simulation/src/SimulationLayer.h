#pragma once

#include <UniverseEngine.h>

#include "CelestialBody.h"

class SimulationLayer : public UE::Layer
{
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;
private:
	UE::Mesh m_PlanetMesh;
	std::unique_ptr<UE::Shader> m_Shader;
	std::unique_ptr<UE::UniformBuffer> m_CameraUniformBuffer;
	std::unique_ptr<UE::UniformBuffer> m_PropertiesUniformBuffer;
	struct Camera
	{
		glm::mat4 ProjectionView;
	};
	Camera m_Camera;
	struct Properties
	{
		glm::mat4 Transformation;
		glm::vec4 Colour;
	};
	Properties m_Properties;

	std::vector<CelestialBody> m_Bodies;
};
