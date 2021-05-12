#include "QBert.h"
#include "Command.h"
#include "GameObject.h"
#include "Scene.h"


#include "ComponentsHeaders.h"
#include "ObserversHeaders.h"
#include "InterfaceWindow.h"
#include "ResourceManager.h"
#include "QBertComponentsHeaders.h"
#include "ServiceLocater.h"
#include "QBertObserver.h"
dae::QBert::QBert()
{

}

void dae::QBert::LoadQbert(Scene& sceneMan, float StartPosx, float StartPosy, GameObject* pblockObject)
{
	ImVec2 posPlayer{ StartPosx,StartPosy };
	ImVec2 posHealthObserver{ 10,100 };
	ImVec2 posDeadObserver{ 100,100 };
	ImVec2 posScoreObserver{ 500,100 };

	const float playerSpace{ 100.f };
	const float textSpace{ 25.f };


	SDL_Color colorHP{ 255,255,255 };
	auto fontHP = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
	
	auto livesObserver{ new dae::LivesObserver({posHealthObserver.x,posHealthObserver.y,new dae::TextComponent("Lives: 20", fontHP, colorHP, false)},
												   {posDeadObserver.x,posDeadObserver.y,new dae::TextComponent("You Died: ", fontHP, colorHP, false)}) };
	auto scoreObserver{ new dae::ScoreObserver({posScoreObserver.x,posScoreObserver.y,new dae::TextComponent("Score: 0", fontHP, colorHP, false)}) };

	//IDK WHY THESE ARE SEPARATED pls fix later
	auto hpComponent{ new dae::LivesComponent(20) };
	auto scoreComponent{ new dae::ScoreComponent(2000) };
	//IDK WHY THESE ARE SEPARATED pls fix later
	hpComponent->AddObserver(livesObserver);
	scoreComponent->AddObserver(scoreObserver);
	scoreComponent->AddObserver(new QBertObserver(28));


	auto QBertObject = std::make_shared<dae::GameObject>(posPlayer.x, posPlayer.y, std::make_shared<TextureComponent>("QBert/QbertCharachter.png", 0.03125f));
	QBertObject->AddBaseComponent(new dae::QuitComponent());
	QBertObject->AddBaseComponent(new dae::PlayerMovement());
	QBertObject->AddBaseComponent(hpComponent);
	QBertObject->AddBaseComponent(scoreComponent);
	
	QBertObject->AddBaseComponent(new dae::QBertMovementComponent(pblockObject));



	sceneMan.Add(QBertObject);
	dae::SceneManager::GetInstance().AddPlayer(QBertObject);
}
