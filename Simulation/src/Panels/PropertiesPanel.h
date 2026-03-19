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
	CelestialBody& GetSelectedBody() { return *m_SelectedBody; }
	const CelestialBody& GetSelectedBody() const { return *m_SelectedBody; }

	bool PreviewOutdated() const { return m_PreviewOutdated; }

	template<typename _Fn>
	void SetDeleteCallback(_Fn&& callback) { m_DeleteCallback = callback; }
	template<typename _Fn>
	void SetSunSelectCallback(_Fn&& callback) { m_SunSelectCallback = callback; }
private:
	UE::Reference<CelestialBody> m_SelectedBody;
	bool m_PreviewOutdated = false;

	std::function<void(CelestialBody& body)> m_DeleteCallback;
	std::function<void(CelestialBody& body)> m_SunSelectCallback;
};
