#pragma once

#include <UniverseEngine.h>

#include <glm/glm.hpp>

class SimulationLayer : public UE::Layer
{
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnRender() override;
private:
	UE::Mesh m_Mesh;
	std::unique_ptr<UE::Shader> m_Shader;
	std::unique_ptr<UE::UniformBuffer> m_MatricesUniformBuffer;
	std::unique_ptr<UE::UniformBuffer> m_PropertiesUniformBuffer;
	struct Matrices
	{
		glm::mat4 ProjectionView;
		glm::mat4 Transformation;
	};
	Matrices m_Matrices;
	struct Properties
	{
		glm::vec4 Colour;
	};
	Properties m_Properties;
};
