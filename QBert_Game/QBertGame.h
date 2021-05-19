#pragma once
#include "QBertLevel.h"
#include "QBertMenu.h"
#include "QBert.h"
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
		QBertMenu m_Menu;
		std::vector<QBertLevel> m_Levels;
		const int m_AmountOfLevels;

	};
}
