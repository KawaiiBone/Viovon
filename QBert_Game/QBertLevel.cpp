#include "QBertLevel.h"
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



dae::QBertLevel::QBertLevel(TypeOfScene typeScene, int windowWidth, int windowHeight, const  Level& level)
	: m_TypeScene(typeScene)
	, m_Map(windowWidth, windowHeight, level)
	, m_LevelInfo(level)
	, m_PlayerStartingCoordinates()
{
	CreateStartingCoordinatesPlayers();
}



void dae::QBertLevel::CreateLevel()
{
	CreateStartingCoordinatesPlayers();
	
	auto& scene = dae::SceneManager::GetInstance().CreateScene(m_TypeScene);

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
	//AddPlayers(scene);

	LoadCoily(m_LevelInfo.coilySpawn, scene);
	LoadUggAbdWrongway(scene);
	LoadSlickAndSam(scene);

	
	scene.SetPlayerStartingCoordinates(m_PlayerStartingCoordinates);





}

void dae::QBertLevel::CreateStartingCoordinatesPlayers()
{

	
	const int collums{ m_LevelInfo.mapSizeColumns - 1 };
	const int rows{ m_LevelInfo.mapSizeColumns - 1 };

	std::vector<AxialCoordinates> tmpVec{ {rows, 0} };
	m_PlayerStartingCoordinates.push_back({ GameMode::singleplayer,tmpVec });

	int randomRow = rand() % (1 + 1) - 1;
	int row{ (rows + randomRow) };

	tmpVec.push_back({ row,1 });

	m_PlayerStartingCoordinates.push_back({ GameMode::versus,tmpVec });

	m_PlayerStartingCoordinates.push_back({ GameMode::coop,{{0,collums},{collums,rows}} });

	
	
	

}

void dae::QBertLevel::AddPlayers(Scene& scene)
{
	for (auto& element: dae::SceneManager::GetInstance().GetPlayers())
	{
		scene.Add(element);
		element->GetComponent<QBertMovementComponent>()->SetBlockObject(m_Map.GetFirstBlock());
		element->SetPosition(m_Map.GetFirstBlock()->GetComponent<MapBlockComponent>()->GetPlatformPos().x, m_Map.GetFirstBlock()->GetComponent<MapBlockComponent>()->GetPlatformPos().y);
	}
}

void dae::QBertLevel::LoadCoily(const bool coilySpawn, Scene& scene) const
{
	if (coilySpawn)
	{

		int randomRow = rand() % (1 + 1) - 1;
		int row{ (m_LevelInfo.mapSizeColumns-1) + randomRow };


		auto m_pBlockObject = scene.GetMapPart(row, 1).second;


		auto CoilyObject = std::make_shared<dae::GameObject>(m_pBlockObject->GetComponent<MapPartComponent>()->GetPlatformPos().x, m_pBlockObject->GetComponent<MapPartComponent>()->GetPlatformPos().y);

		std::vector<std::pair<std::string, std::string>> tmpNames{ {"QBert/CoilyBallForm.png","CoilyBall"},{"QBert/Coily.png","Coily"} };
		CoilyObject->AddPairComponent(new QbertTexturesComponent(2.f, tmpNames), new CoilyAiComponent(row, { "CoilyBall","Coily" }, m_LevelInfo.coilySpawnTime));
		CoilyObject->SetRenderStatus(false);
		scene.Add(CoilyObject);
	}
}

void dae::QBertLevel::LoadUggAbdWrongway(Scene& scene) const
{
	for (float element : m_LevelInfo.uggAbdWrongwaySpawnTimes)
	{
		int randomRow3 = rand() % (1 + 1) - 1;
		int row3{ (m_LevelInfo.mapSizeColumns - 1) };
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
			uggObject->AddPairComponent(new QbertTexturesComponent(2.f, tmpNames3), new UggOrWrongwayAiComponent(row3, { tmpNames3[0].second,tmpNames3[0].second }, element));
			uggObject->SetRenderStatus(false);
			scene.Add(uggObject);
		}
		else
		{
			auto uggObject = std::make_shared<dae::GameObject>(m_pBlockObject3->GetComponent<MapPartComponent>()->GetWrongWayPlatformPos().x, m_pBlockObject3->GetComponent<MapPartComponent>()->GetWrongWayPlatformPos().y);
			uggObject->AddPairComponent(new QbertTexturesComponent(2.f, tmpNames3), new UggOrWrongwayAiComponent(row3, { tmpNames3[0].second,tmpNames3[0].second }, element));
			uggObject->SetRenderStatus(false);
			scene.Add(uggObject);
		}
	}
}

void dae::QBertLevel::LoadSlickAndSam(Scene& scene) const
{
	for (float element : m_LevelInfo.slickAndSamSpawnTimes)
	{
		element;
		int randomRow2 = rand() % (1 + 1) - 1;
		int row2{ (m_LevelInfo.mapSizeColumns - 1) + randomRow2 };


		auto m_pBlockObject2 = scene.GetMapPart(row2, 1).second;

		auto slickOrSamObject = std::make_shared<dae::GameObject>(m_pBlockObject2->GetComponent<MapPartComponent>()->GetPlatformPos().x, m_pBlockObject2->GetComponent<MapPartComponent>()->GetPlatformPos().y);


		std::vector<std::pair<std::string, std::string>> tmpNames2{ {"QBert/Slick.png","Slick"} };
		slickOrSamObject->AddPairComponent(new QbertTexturesComponent(2.f, tmpNames2), new SlickOrSlamAiComponent(row2, { "Slick","Slick" }, element));
		slickOrSamObject->SetRenderStatus(false);
		scene.Add(slickOrSamObject);
	}
}
