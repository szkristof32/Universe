#include "GridRenderer.h"

using namespace UniverseEngine;

GridRenderer::GridRenderer()
{
	m_Shader = MakeUnique<Shader>();
	m_Shader->LoadFromDisk("GridShader");
}

void GridRenderer::Configure(const GridRendererConfig& config)
{
	m_Config = config;
}

void GridRenderer::BeginFrame()
{
	m_Shader->Bind();
	m_Config.CameraUniformBuffer->Bind();
}

void GridRenderer::EndFrame()
{
}

void GridRenderer::DrawGrid()
{
	constexpr uint32_t axisCount = 2;
	constexpr uint32_t verticesPerAxis = 2;
	constexpr uint32_t linesPerAxis = 500;

	RendererAPIConfiguration& rendererAPIConfig = RendererAPI::GetConfiguration();
	rendererAPIConfig.LineWidth = 2.0f;
	rendererAPIConfig.EnableDepthTest = true;
	rendererAPIConfig.EnableBlending = true;

	RendererAPI::Configure();

	RendererAPI::Draw(axisCount * verticesPerAxis * (linesPerAxis + 1), PrimitiveMode::LineList);
}
