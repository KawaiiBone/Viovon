#pragma once
#include "Scene.h"
namespace dae
{
	class QBert;
	class QBertMenu
	{
	public:
		QBertMenu(TypeOfScene typeScene);
		void CreateMenu(QBert& qbertP2);
	private:
		void CreateMenuObjects(Scene& scene);
		
		const TypeOfScene m_TypeScene;
	};
}