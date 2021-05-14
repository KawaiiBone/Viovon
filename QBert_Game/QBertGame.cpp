#include "QBertGame.h"
#include "Command.h"
#include "GameObject.h"
#include "Scene.h"


#include "ComponentsHeaders.h"
#include "InputManager.h"
#include "ObserversHeaders.h"
#include "InterfaceWindow.h"
#include "ResourceManager.h"
#include "QBertCommands.h"
#include "ServiceLocater.h"

dae::QBertGame::QBertGame(int windowWidth, int windowHeight):
	m_Map(windowWidth, windowHeight)
{
	
}

void dae::QBertGame::LoadQbertGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene(TypeOfScene::demo);

	auto backgroundObject = std::make_shared<dae::GameObject>(0.f, 0.f, std::make_shared<TextureComponent>("background.jpg"));
	scene.AddBackground(backgroundObject/*, false*/);

	auto logoObject = std::make_shared<dae::GameObject>(216.f, 180.f, std::make_shared<TextureComponent>("logo.png"));
	scene.Add(logoObject/*, false*/);

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
	
	
	m_QBert.LoadQbert(scene, m_Map.GetQbertSpawnPos().GetPosition().x, m_Map.GetQbertSpawnPos().GetPosition().y, m_Map.GetFirstBlock());








	//input.AddDefaultCommandAndKey({ std::make_shared<MoveLeftUp>(), OperateKey::pressedDown, LeftButton });
	//input.AddDefaultCommandAndKey({ std::make_shared<MoveRight>(), OperateKey::pressedDown, RightButton });
	//input.AddDefaultCommandAndKey({ std::make_shared<MoveUp>(), OperateKey::pressedDown, UpButton });
	//input.AddDefaultCommandAndKey({ std::make_shared<MoveDown>(), OperateKey::pressedDown, DownButton });





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
