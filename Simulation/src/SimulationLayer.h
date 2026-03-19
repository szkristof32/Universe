#pragma once

#include <UniverseEngine.h>

#include "CelestialBody.h"
#include "CameraController.h"

#include "Rendering/PlanetRenderer.h"
#include "Rendering/PreviewRenderer.h"
#include "Rendering/GridRenderer.h"

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

	void UpdateVelocity(CelestialBody& body, UE::Timestep delta);
	void UpdatePosition(CelestialBody& body, UE::Timestep delta);

	void GeneratePreview();
private:
	CameraController m_CameraController;
	Camera m_Camera;

	bool m_ViewportFocused = false;
	bool m_UsingGizmo = false;
	glm::vec2 m_ViewportSize;

	PlanetRenderer m_Renderer;
	PreviewRenderer m_PreviewRenderer;
	GridRenderer m_GridRenderer;

	std::vector<CelestialBody> m_Bodies;
	std::vector<LineSegment> m_PreviewSegments;
	bool m_PreviewOutdated = true;
	float m_PreviewUpdateRate = 0.3f;
	bool m_ShowPreview = true;

	float m_SimulationSpeed = 1.0f;
	float m_GravitationalConstant = 0.0001f;
	bool m_EnableSimulation = false;

	std::unique_ptr<PropertiesPanel> m_PropertiesPanel;
	std::unique_ptr<BodiesPanel> m_BodiesPanel;
};
