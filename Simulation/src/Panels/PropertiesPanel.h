#pragma once

#include <UniverseEngine.h>

#include "CelestialBody.h"

class PropertiesPanel
{
public:
	void OnUIRender();

	void SetSelectedBody(CelestialBody& body) { m_SelectedBody = &body; }
	void ClearSelectedBody() { m_SelectedBody = nullptr; }

	bool HasSelected() const { return m_SelectedBody != nullptr; }
	const CelestialBody& GetSelectedBody() const { return *m_SelectedBody; }

	template<typename _Fn>
	void SetDeleteCallback(_Fn&& callback) { m_DeleteCallback = callback; }
private:
	UE::Reference<CelestialBody> m_SelectedBody;

	std::function<void(CelestialBody& body)> m_DeleteCallback;
};
