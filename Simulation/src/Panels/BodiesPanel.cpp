#include "BodiesPanel.h"

#include <imgui.h>

void BodiesPanel::OnUIRender()
{
	ImGui::Begin("Bodies");

	ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen;

	if (ImGui::TreeNodeEx("Bodies", treeNodeFlags))
	{
		treeNodeFlags |= ImGuiTreeNodeFlags_Leaf;

		for (size_t i = 0; i < m_Bodies->size(); i++)
		{
			const auto& body = m_Bodies->at(i);

			bool selected = m_SelectedBody == i;

			if (ImGui::TreeNodeEx(body.Name.c_str(), treeNodeFlags | (selected ? ImGuiTreeNodeFlags_Selected : 0)))
				ImGui::TreePop();

			if ((ImGui::IsItemClicked() || ImGui::IsItemFocused()) && m_SelectBodyCallback)
				m_SelectedBody = (uint32_t)i;
		}

		ImGui::TreePop();
	}

	if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
		m_SelectedBody = -1;

	if (ImGui::Button("Add body"))
	{
		CelestialBody bodyToAdd{};
		bodyToAdd.Colour = glm::vec4(1.0f);
		bodyToAdd.Radius = 1.0f;
		bodyToAdd.SurfaceGravity = 10.0f;
		bodyToAdd.CalculateMass();

		m_Bodies->emplace_back(std::move(bodyToAdd));
	}

	ImGui::End();

	if (m_SelectedBody != -1 && m_SelectBodyCallback)
		m_SelectBodyCallback(m_Bodies->at(m_SelectedBody));
	else if (m_DeselectBodyCallback)
		m_DeselectBodyCallback();
}
