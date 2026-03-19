#include "PreviewRenderer.h"

using namespace UniverseEngine;

PreviewRenderer::PreviewRenderer()
{
	m_Shader = MakeUnique<Shader>();
	m_Shader->LoadFromDisk("PreviewShader");

	m_VertexArray = MakeUnique<VertexArray>();
	m_VertexArray->Bind();

	m_Buffer = MakeUnique<VertexBuffer>(Buffer(sizeof(LineSegment)));
	m_Buffer->Bind();

	m_VertexArray->AddAttribute(AttributeType::Float3);
	m_VertexArray->AddAttribute(AttributeType::Float4);
	m_VertexArray->BakeLayout();
}

void PreviewRenderer::Configure(const PreviewRendererConfig& config)
{
	m_Config = config;
}

void PreviewRenderer::BeginFrame()
{
	m_Shader->Bind();
}

void PreviewRenderer::EndFrame()
{
}

void PreviewRenderer::DrawPreview(const std::vector<LineSegment>& segments)
{
	m_VertexArray->Bind();
	m_Buffer->Bind();
	m_Buffer->SetData(Buffer(const_cast<LineSegment*>(segments.data()), segments.size() * sizeof(LineSegment)));
	m_Config.CameraUniformBuffer->Bind();

	RendererAPIConfiguration& rendererAPIConfig = RendererAPI::GetConfiguration();
	rendererAPIConfig.LineWidth = 2.0f;

	RendererAPI::Configure();

	RendererAPI::Draw((uint32_t)segments.size() * 4, PrimitiveMode::LineList);
}
