#include "PlanetRenderer.h"

using namespace UniverseEngine;

#include <glm/gtc/matrix_transform.hpp>

PlanetRenderer::PlanetRenderer()
{
	m_PlanetMesh = m_MeshGenerator.GenerateSphere();

	FramebufferSpecification framebufferSpec{};
	framebufferSpec.Width = 1280;
	framebufferSpec.Height = 720;
	framebufferSpec.Attachments = {
		FramebufferAttachmentType::ColourAttachment,
		FramebufferAttachmentType::DepthAttachment
	};
	m_Framebuffer = MakeUnique<Framebuffer>(framebufferSpec);

	m_Shader = MakeUnique<Shader>();
	m_Shader->LoadFromDisk("PlanetShader");

	m_CameraUniformBuffer = MakeUnique<UniformBuffer>(Buffer(sizeof(m_Camera)));
	m_CameraUniformBuffer->BindToShader(0);

	m_Properties.Transformation = glm::mat4(1.0f);
	m_Properties.Colour = glm::vec4(0.8f, 0.2f, 0.3f, 1.0f);
	m_PropertiesUniformBuffer = MakeUnique<UniformBuffer>(Buffer(&m_Properties, sizeof(m_Properties)));
	m_PropertiesUniformBuffer->BindToShader(1);
}

void PlanetRenderer::BeginFrame(Camera& camera, const glm::vec2& viewportSize)
{
	if (m_ViewportSize != viewportSize)
	{
		m_ViewportSize = viewportSize;
		m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
	}

	m_Framebuffer->Bind();

	m_Shader->Bind();
	m_CameraUniformBuffer->Bind();
	m_PropertiesUniformBuffer->Bind();

	m_PlanetMesh.GetVertexArray()->Bind();
	m_PlanetMesh.GetVertexBuffer()->Bind();
	m_PlanetMesh.GetIndexBuffer()->Bind();

	if (camera != m_Camera)
	{
		m_Camera = camera;
		m_CameraUniformBuffer->SetData(Buffer(&m_Camera, sizeof(m_Camera)));
	}

	RendererAPIConfiguration rendererAPIConfig{};
	rendererAPIConfig.EnableDepthTest = true;

	RendererAPI::Configure(rendererAPIConfig);
}

void PlanetRenderer::EndFrame()
{
	auto window = Application::Get()->GetWindow();
	m_Framebuffer->Unbind(window->GetWidth(), window->GetHeight());
}

void PlanetRenderer::DrawPlanet(const CelestialBody& planet)
{
	m_Properties.Transformation = glm::translate(glm::mat4(1.0f), planet.Position) *
		glm::scale(glm::mat4(1.0f), glm::vec3(planet.Radius));
	m_Properties.Colour = planet.Colour;
	m_PropertiesUniformBuffer->SetData(Buffer(&m_Properties, sizeof(m_Properties)));

	RendererAPI::DrawIndexed(m_PlanetMesh.GetIndexCount(), PrimitiveMode::TriangleList);
}
