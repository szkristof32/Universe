#include "PropertiesPanel.h"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <glm/gtc/type_ptr.hpp>

void PropertiesPanel::OnUIRender()
{
	ImGui::Begin("Properties");

	if (!m_SelectedBody)
	{
		ImGui::Text("Select a body to see its properties");
	}
	else
	{
		ImGui::InputText("Name", &m_SelectedBody->Name);
		ImGui::ColorEdit4("Colour", glm::value_ptr(m_SelectedBody->Colour));
		if (ImGui::DragFloat3("Position", glm::value_ptr(m_SelectedBody->Position), 0.01f))
			m_PreviewOutdated = true;
		if (ImGui::DragFloat3("Velocity", glm::value_ptr(m_SelectedBody->Velocity), 0.01f))
			m_PreviewOutdated = true;
		if (ImGui::DragFloat("Radius", &m_SelectedBody->Radius, 0.01f, 0.1f))
		{
			m_SelectedBody->CalculateMass();
			m_PreviewOutdated = true;
		}
		if (ImGui::DragFloat("Surface gravity", &m_SelectedBody->SurfaceGravity, 0.01f))
		{
			m_SelectedBody->CalculateMass();
			m_PreviewOutdated = true;
		}

		if (ImGui::Checkbox("Center of gravity", &m_SelectedBody->Sun))
			m_PreviewOutdated = true;
		if (m_SelectedBody->Sun && m_SunSelectCallback)
			m_SunSelectCallback(*m_SelectedBody);

		if (ImGui::Button("Delete"))
		{
			ImGui::OpenPopup("Confirmation");
		}

		if (ImGui::BeginPopupModal("Confirmation", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Are you sure you want to delete the body?");

			ImGui::Spacing();
			ImGui::Spacing();

			ImGuiStyle& style = ImGui::GetStyle();
			float width = ImGui::CalcTextSize("Yes").x + ImGui::CalcTextSize("Cancel").x + 10.0f;
			float offset = (ImGui::GetContentRegionAvail().x - width) / 2.0f;
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);

			if (ImGui::Button("Yes"))
			{
				if (m_DeleteCallback)
					m_DeleteCallback(*m_SelectedBody);
				ClearSelectedBody();
				ImGui::CloseCurrentPopup();
				m_PreviewOutdated = true;
			}
			ImGui::SameLine(0.0f, 10.0f);
			if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

	ImGui::End();
}
