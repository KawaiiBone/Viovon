#pragma once
#include "Scene.h"
namespace dae
{

	class QBertMenu
	{
	public:
		QBertMenu(TypeOfScene typeScene);
		void CreateMenu();
	private:
		
		const TypeOfScene m_TypeScene;
	};
}