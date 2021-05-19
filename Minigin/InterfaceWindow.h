#pragma once
#include <functional>
#include <string>
#include "imgui.h"
#include <vector>
namespace dae
{
	enum class InterFaceNames;
	struct InterfacePart
	{
		std::pair<std::string, ImVec2> button;
		std::string text;
		InterFaceNames interFaceName;
		std::function<void()> myFunctionWrapper;
	};
	
	class InterfaceWindow
	{
	public:
		InterfaceWindow(std::string titleName, InterFaceNames interFaceName);
		
		void AddInterfacePart(const InterfacePart& interFaceButton);
		void Render(InterFaceNames& interFaceName) ;
		InterFaceNames GetInterFaceName();

	
	private:
		
		 std::string m_TitleName;
		std::vector<InterfacePart> m_InterfaceButtonVec;
		InterFaceNames m_InterFaceName;
	};
}
