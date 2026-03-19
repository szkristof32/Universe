#pragma once

#include <UniverseEngine.h>

struct GridRendererConfig
{
	UE::Reference<UE::UniformBuffer> CameraUniformBuffer;
};

class GridRenderer
{
public:
	GridRenderer();

	void Configure(const GridRendererConfig& config);

	void BeginFrame();
	void EndFrame();

	void DrawGrid();
private:
	GridRendererConfig m_Config;

	std::unique_ptr<UE::Shader> m_Shader;
	std::unique_ptr<UE::VertexArray> m_VertexArray;
	std::unique_ptr<UE::VertexBuffer> m_Buffer;
};
