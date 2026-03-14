#pragma once

#include <UniverseEngine.h>

#include "CelestialBody.h"
#include "PlanetRenderer.h"
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
	CameraController m_CameraController;
	Camera m_Camera;

	bool m_ViewportFocused = false;
	glm::vec2 m_ViewportSize;

	PlanetRenderer m_Renderer;

	std::vector<CelestialBody> m_Bodies;

	std::unique_ptr<PropertiesPanel> m_PropertiesPanel;
	std::unique_ptr<BodiesPanel> m_BodiesPanel;
};
