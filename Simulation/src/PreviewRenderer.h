#pragma once

#include <UniverseEngine.h>

#include "PlanetRenderer.h"

struct PreviewRendererConfig
{
	UE::Reference<UE::Framebuffer> RenderTarget;
	UE::Reference<UE::UniformBuffer> CameraUniformBuffer;
};

struct LineVertex
{
	glm::vec3 Position;
	glm::vec4 Colour;
};

struct LineSegment
{
	LineVertex Start;
	LineVertex End;
};

class PreviewRenderer
{
public:
	PreviewRenderer();

	void Configure(const PreviewRendererConfig& config);

	void BeginFrame();
	void EndFrame();

	void DrawPreview(const std::vector<LineSegment>& segments);
private:
	PreviewRendererConfig m_Config;
	
	std::unique_ptr<UE::Shader> m_Shader;
	std::unique_ptr<UE::VertexArray> m_VertexArray;
	std::unique_ptr<UE::VertexBuffer> m_Buffer;
};
