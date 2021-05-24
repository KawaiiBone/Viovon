#include "QBert.h"
#include "Command.h"
#include "GameObject.h"
#include "Scene.h"


#include "ComponentsHeaders.h"
#include "ObserversHeaders.h"
#include "InterfaceWindow.h"
#include "ResourceManager.h"
#include "QBertComponentsHeaders.h"
dae::QBert::QBert(int playerIndex):
	m_PlayerIndex{playerIndex}

{
	
}
void dae::QBert::CreateQbert()
{
	ImVec2 posPlayer{ 0.f, 0.f };
	ImVec2 posHealthObserver{ 10,200 -float(m_PlayerIndex * 50) };
	ImVec2 posDeadObserver{ 100,200 };
	ImVec2 posScoreObserver{ 500 ,200 - float(m_PlayerIndex * 50) };

	const float playerSpace{ 100.f };
	const float textSpace{ 25.f };


	SDL_Color colorHP{ 255,255,255 };
	auto fontHP = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);

	auto livesObserver{ new dae::LivesObserver({posHealthObserver.x,posHealthObserver.y,new dae::TextComponent("Lives: 3", fontHP, colorHP, false)},
												   {posDeadObserver.x,posDeadObserver.y,new dae::TextComponent("You Died: ", fontHP, colorHP, false)}) };
	auto scoreObserver{ new dae::ScoreObserver({posScoreObserver.x,posScoreObserver.y,new dae::TextComponent("Score: 0", fontHP, colorHP, false)}) };


	auto hpComponent{ new dae::LivesComponent(3) };
	auto scoreComponent{ new dae::ScoreComponent(20000) };

	hpComponent->AddObserver(livesObserver);
	scoreComponent->AddObserver(scoreObserver);
	//scoreComponent->AddObserver(new QBertObserver(28));

	std::string adressTexture;
	if (m_PlayerIndex == 0)
	{
		adressTexture = "QBert/QbertCharachter.png";
	}
	else
	{
		adressTexture = "QBert/QbertCharachter2.png";
	}
	auto QBertObject = std::make_shared<dae::GameObject>(posPlayer.x, posPlayer.y, std::make_shared<TextureComponent>(adressTexture, 0.03125f));
	QBertObject->AddBaseComponent(new dae::QuitComponent());
	//QBertObject->AddBaseComponent(new dae::PlayerMovement());
	QBertObject->AddBaseComponent(hpComponent);
	QBertObject->AddBaseComponent(scoreComponent);
//	QBertObject->AddBaseComponent(new dae::QBertMovementComponent(/*BlockObject*/nullptr, 6, 0));
	QBertObject->AddBaseComponent(new dae::PLayerComponent(/*BlockObject*/nullptr, 6, 0, "../Data/Sounds/QBertjump.wav"));
	dae::SceneManager::GetInstance().AddPlayer(QBertObject);
}

