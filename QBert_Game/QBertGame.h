#pragma once
#include "QBert.h"
#include "QBertMap.h"
namespace dae
{

	class QBertGame
	{
	public:
		QBertGame(int windowWidth, int windowHeight);
		void LoadQbertGame();
	private:
		void LoadQbertCommandKeys();
		dae::QBert m_QBert;
		dae::QBertMap m_Map;

	};
}
