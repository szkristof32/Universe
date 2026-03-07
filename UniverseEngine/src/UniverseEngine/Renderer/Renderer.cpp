#include "pch.h"
#include "Renderer.h"

#include "UniverseEngine/Renderer/RendererAPI.h"

namespace UniverseEngine {

	Renderer::Renderer()
	{
		m_Context = MakeUnique<Context>();
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::BeginFrame()
	{
		m_Context->BeginFrame();
	}

	void Renderer::EndFrame()
	{
		m_Context->EndFrame();
	}

}
