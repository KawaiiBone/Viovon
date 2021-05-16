#include "QBertGame.h"
#include "Command.h"
#include "GameObject.h"
#include "Scene.h"


#include "ComponentsHeaders.h"
#include "InputManager.h"
#include "InterfaceWindow.h"
#include "ResourceManager.h"
#include "QBertCommands.h"
#include "QbertTexturesComponent.h"
#include "ServiceLocater.h"
#include "UggOrWrongwayAiComponent.h"

dae::QBertGame::QBertGame(int windowWidth, int windowHeight) :
	m_Map(windowWidth, windowHeight)
{

}

void dae::QBertGame::LoadQbertGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene(TypeOfScene::demo);

	auto backgroundObject = std::make_shared<dae::GameObject>(0.f, 0.f, std::make_shared<TextureComponent>("background.jpg"));
	scene.AddBackground(backgroundObject/*, false*/);

	auto logoObject = std::make_shared<dae::GameObject>(216.f, 180.f, std::make_shared<TextureComponent>("logo.png"));
	scene.AddBackground(logoObject/*, false*/);
	//scene.Add(logoObject/*, false*/);

	SDL_Color colorTitle{ 255,255,255 };
	auto fontTitle = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto daeTitleObject = std::make_shared<dae::GameObject>(80.f, 20.f, std::make_shared<TextComponent>("Programming 4 Assignment", fontTitle, colorTitle, true));
	scene.Add(daeTitleObject/*, false*/);


	SDL_Color colorFps{ 255,0,0 };
	auto fontFps = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto FpsObject = std::make_shared<dae::GameObject>(0.f, 10.f);
	FpsObject->AddPairComponent(new dae::TextComponent("FPS", fontFps, colorFps, false), new dae::FPSComponent());
	scene.Add(FpsObject/*, false*/);

	m_Map.LoadMap(scene);
	m_QBert.LoadQbert(scene, m_Map.GetFirstBlock());

	
	srand(unsigned int(time(nullptr)));

	int randomRow = rand() % (1 + 1) - 1;
	int row{ 6 + randomRow };


	auto m_pBlockObject = scene.GetMapPart(row, 1).second;


	auto CoilyObject = std::make_shared<dae::GameObject>(m_pBlockObject->GetComponent<MapPartComponent>()->GetPlatformPos().x, m_pBlockObject->GetComponent<MapPartComponent>()->GetPlatformPos().y);

	std::vector<std::pair<std::string, std::string>> tmpNames{ {"QBert/CoilyBallForm.png","CoilyBall"},{"QBert/Coily.png","Coily"} };
	CoilyObject->AddPairComponent(new QbertTexturesComponent(2.f, tmpNames), new CoilyAiComponent(row, { "CoilyBall","Coily" }));
	scene.Add(CoilyObject);

	int randomRow2 = rand() % (1 + 1) - 1;
	int row2{ 6 + randomRow2 };


	auto m_pBlockObject2 = scene.GetMapPart(row2, 1).second;

	auto slickObject = std::make_shared<dae::GameObject>(m_pBlockObject2->GetComponent<MapPartComponent>()->GetPlatformPos().x, m_pBlockObject2->GetComponent<MapPartComponent>()->GetPlatformPos().y);


	std::vector<std::pair<std::string, std::string>> tmpNames2{ {"QBert/Slick.png","Slick"} };
	slickObject->AddPairComponent(new QbertTexturesComponent(2.f, tmpNames2), new SlickOrSlamAiComponent(row2, { "Slick","Slick" }));
	scene.Add(slickObject);


	int randomRow3 = rand() % (1 + 1) - 1;
	int row3{ 6};
	std::vector<std::pair<std::string, std::string>> tmpNames3{};
	if (randomRow3 == 0)
	{
		tmpNames3.push_back({ "QBert/Wrongway.png","Wrongway" });
		row3 = 0;
	}
	else
	{
		tmpNames3.push_back({ "QBert/Ugg.png","Ugg" });
	}

	auto m_pBlockObject3 = scene.GetMapPart(row3, 6).second;
	if (randomRow3 == 0)
	{
		auto uggObject = std::make_shared<dae::GameObject>(m_pBlockObject3->GetComponent<MapPartComponent>()->GetUggPlatformPos().x, m_pBlockObject3->GetComponent<MapPartComponent>()->GetUggPlatformPos().y);
		uggObject->AddPairComponent(new QbertTexturesComponent(2.f, tmpNames3), new UggOrWrongwayAiComponent(row3, { tmpNames3[0].second,tmpNames3[0].second }));
		scene.Add(uggObject);
	}
	else
	{
		auto uggObject = std::make_shared<dae::GameObject>(m_pBlockObject3->GetComponent<MapPartComponent>()->GetWrongWayPlatformPos().x, m_pBlockObject3->GetComponent<MapPartComponent>()->GetWrongWayPlatformPos().y);
		uggObject->AddPairComponent(new QbertTexturesComponent(2.f, tmpNames3), new UggOrWrongwayAiComponent(row3, { tmpNames3[0].second,tmpNames3[0].second }));
		scene.Add(uggObject);
	}
	




	LoadQbertCommandKeys();

}

void dae::QBertGame::LoadQbertCommandKeys()
{
	auto& input = InputManager::GetInstance();

	input.AddDefaultCommandAndKey({ std::make_shared<MoveLeftDown>(), OperateKey::keyStrokeDown, LeftButton });
	input.AddDefaultCommandAndKey({ std::make_shared<MoveRightUp>(), OperateKey::keyStrokeDown, RightButton });
	input.AddDefaultCommandAndKey({ std::make_shared<MoveLeftUp>(), OperateKey::keyStrokeDown, UpButton });
	input.AddDefaultCommandAndKey({ std::make_shared<MoveRightDown>(), OperateKey::keyStrokeDown, DownButton });
}
