#pragma once
#include <string>
#include "imgui.h"
namespace dae
{
	enum class InterFaceNames;
	struct InterfacePart
	{
		std::pair<std::string, ImVec2> button;
		std::string text;
		InterFaceNames interFaceName;
	};
	
	class InterfaceWindow
	{
	public:
		InterfaceWindow(std::string titleName, InterFaceNames interFaceName);
		
		void AddInterfacePart(const InterfacePart& interFaceButton);
		void Render(InterFaceNames& interFaceName);
		InterFaceNames GetInterFaceName();
	
	private:

		 std::string m_TitleName;
		std::vector<InterfacePart> m_InterfaceButtonVec;
		InterFaceNames m_InterFaceName;
	};
}
