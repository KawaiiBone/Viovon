
#include <Minigin.h>
//#include <vld.h>
#include <../Visual_Leak_Detector/include/vld.h>
#include "QBertGame.h"


int main(int, char* []) {
	dae::Minigin engine;
	
	dae::QBertGame m_QBertGame{ engine.GetWindowSize().width, engine.GetWindowSize().height};
	m_QBertGame.LoadQbertGame();
	engine.Run();
	return 0;
	
}