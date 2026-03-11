#pragma once

#include <UniverseEngine.h>

#include "CelestialBody.h"

#include <vector>

class BodiesPanel
{
public:
	void OnUIRender();

	void SetBodies(std::vector<CelestialBody>& bodies) { m_Bodies = &bodies; }

	template<typename _Fn>
	void SetSelectBodyCallback(_Fn&& callback) { m_SelectBodyCallback = callback; }
	template<typename _Fn>
	void SetDeselectBodyCallback(_Fn&& callback) { m_DeselectBodyCallback = callback; }
private:
	UE::Reference<std::vector<CelestialBody>> m_Bodies;
	uint32_t m_SelectedBody = -1;

	std::function<void(CelestialBody&)> m_SelectBodyCallback;
	std::function<void()> m_DeselectBodyCallback;
};
