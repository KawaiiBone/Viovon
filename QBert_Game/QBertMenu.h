#pragma once
#include "Scene.h"
namespace dae
{
	class QBert;
	class CoilyPlayer;
	class QBertMenu
	{
	public:
		QBertMenu(TypeOfScene typeScene);
		void CreateMenu(QBert& qbertP2, CoilyPlayer& coilyP2);
	private:
		void CreateMenuObjects(Scene& scene)const;
		void CreateHowToPlayString();
		std::string m_HowToPlayString;
		const TypeOfScene m_TypeScene;
	};
}