#include "CoilyPlayer.h"
#include "GameObject.h"
#include "PLayerCoilyComponent.h"
#include "QbertTexturesComponent.h"
#include "QuitComponent.h"
#include "SceneManager.h"

dae::CoilyPlayer::CoilyPlayer(int playerIndex):
	m_PlayerIndex(playerIndex)
{
}

void dae::CoilyPlayer::CreateCoily() const
{


	const float playerSpace{ 100.f };
	const float textSpace{ 25.f };


	int randomRow = rand() % (1 + 1) - 1;
	const int row{ 6 + randomRow };

	std::string adressTexture;

	std::vector<std::pair<std::string, std::string>> tmpNames{ {"QBert/CoilyBallForm.png","CoilyBall"},{"QBert/Coily.png","Coily"} };
	auto CoilyObject = std::make_shared<dae::GameObject>(0.f, 0.f);
	CoilyObject->AddPairComponent(new QbertTexturesComponent(2.f, tmpNames), new PLayerCoilyComponent(nullptr, row,1,{ "CoilyBall","Coily" }, "../Data/Sounds/Coilyjump.wav"));
	CoilyObject->AddBaseComponent(new dae::QuitComponent());
	dae::SceneManager::GetInstance().AddPlayer(CoilyObject);
}
