#include "MiniginPCH.h"
#include "InterfaceWindow.h"
#include "imgui.h"

dae::InterfaceWindow::InterfaceWindow(std::string titleName, InterFaceNames interFaceName) :
	m_TitleName(   titleName ), m_InterfaceButtonVec(), m_InterFaceName{ interFaceName }
{
}

void dae::InterfaceWindow::AddInterfacePart(const InterfacePart& interFaceButton)
{
	m_InterfaceButtonVec.push_back(interFaceButton);
}

void dae::InterfaceWindow::Render(InterFaceNames& interFaceName)
{
	if (interFaceName == m_InterFaceName)
	{


		ImGui::Begin((m_TitleName.c_str()));

		for (auto interFaceButton : m_InterfaceButtonVec)
		{
			if (interFaceButton.text != Invalid_String)
			{
				ImGui::Text(interFaceButton.text.c_str());
			}
			if (interFaceButton.button.first != Invalid_String && ImGui::Button(interFaceButton.button.first.c_str(), interFaceButton.button.second))
			{
				interFaceName = interFaceButton.interFaceName;

			}
		}

		ImGui::End();
	}
}

dae::InterFaceNames dae::InterfaceWindow::GetInterFaceName()
{
	return m_InterFaceName;
}
