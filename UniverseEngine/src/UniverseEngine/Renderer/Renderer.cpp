#include "pch.h"
#include "Renderer.h"

namespace UniverseEngine {

	Renderer::Renderer()
	{
		m_Context = std::make_unique<Context>();
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
