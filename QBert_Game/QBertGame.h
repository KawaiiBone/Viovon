#pragma once
#include "QBertLevel.h"
#include "QBertMenu.h"
#include "QBert.h"
#include "CoilyPlayer.h"
namespace dae
{




	struct Level;
	class QBertGame
	{
	public:
		QBertGame(int windowWidth, int windowHeight);
		void LoadQbertGame();
	private:

		void LoadQbertCommandKeys();
		Level ReadLevelFile(int index);
		QBert m_QBertPlayerOne;
		QBert m_QBertPlayerTwo;
		CoilyPlayer m_CoilyPlayerTwo;
		QBertMenu m_Menu;
		std::vector<QBertLevel> m_Levels;
		const int m_AmountOfLevels;
		const int m_Volume;
		
	

	};
}
