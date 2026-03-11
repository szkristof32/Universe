#pragma once

#include "UniverseEngine/Core/Layer.h"

namespace UniverseEngine {

	class ImGuiLayer : public Layer
	{
	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnEvent(Event& e) override;

		void BeginFrame();
		void EndFrame();
	};

}
