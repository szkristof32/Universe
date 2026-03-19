#pragma once

#include <UniverseEngine.h>

#include "CelestialBody.h"
#include "MeshGenerator.h"

struct Camera
{
	glm::mat4 Projection;
	glm::mat4 View;
};

inline bool operator==(const Camera& a, const Camera& b)
{
	return a.Projection == b.Projection && a.View == b.View;
}
inline bool operator!=(const Camera& a, const Camera& b)
{
	return !(a == b);
}

class PlanetRenderer
{
public:
	PlanetRenderer();

	void BeginFrame(Camera& camera, const glm::vec2& viewportSize);
	void EndFrame();

	void Prepare();
	void DrawPlanet(const CelestialBody& planet);

	uint32_t GetFinalImage() const { return m_Framebuffer->GetColourAttachment(); }

	UE::Reference<UE::Framebuffer> GetFramebuffer() const { return m_Framebuffer; }
	UE::Reference<UE::UniformBuffer> GetCameraUniformBuffer() const { return m_CameraUniformBuffer; }
private:
	MeshGenerator m_MeshGenerator;
	UE::Mesh m_PlanetMesh;
	
	std::unique_ptr<UE::Framebuffer> m_Framebuffer;
	std::unique_ptr<UE::Shader> m_Shader;

	std::unique_ptr<UE::UniformBuffer> m_CameraUniformBuffer;
	std::unique_ptr<UE::UniformBuffer> m_PropertiesUniformBuffer;
	
	glm::vec2 m_ViewportSize;
	Camera m_Camera;
	struct Properties
	{
		glm::mat4 Transformation;
		glm::vec4 Colour;
	};
	Properties m_Properties;
};
