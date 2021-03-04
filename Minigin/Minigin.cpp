#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "Command.h"
#include "GameObject.h"
#include "Scene.h"


#include "ComponentsHeaders.h"
#include "ObserversHeaders.h"
#include "InterfaceWindow.h"




using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{



	CreateUI();

	

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto backgroundObject = std::make_shared<GameObject>(0.f, 0.f, new TextureComponent("background.jpg"));
	scene.Add(backgroundObject/*, false*/);

	auto logoObject = std::make_shared<GameObject>(216.f, 180.f, new TextureComponent("logo.png"));
	scene.Add(logoObject/*, false*/);

	SDL_Color colorTitle{ 255,255,255 };
	auto fontTitle = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto daeTitleObject = std::make_shared<GameObject>(80.f, 20.f, new TextComponent("Programming 4 Assignment", fontTitle, colorTitle, true));
	scene.Add(daeTitleObject/*, false*/);


	SDL_Color colorFps{ 255,0,0 };
	auto fontFps = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto FpsObject = std::make_shared<GameObject>(0.f, 10.f);
	FpsObject->AddPairComponent(new TextComponent("FPS", fontFps, colorFps, false), new FPSComponent());
	scene.Add(FpsObject/*, false*/);




	auto QBertObject = std::make_shared<GameObject>(50.f, 50.f, new TextureComponent("QBert/QbertCharachter.png", 0.25f));
	QBertObject->AddBaseComponent(new QuitComponent());
	QBertObject->AddBaseComponent(new PlayerMovement());
	QBertObject->AddBaseComponent(new HealthComponent(20));
	QBertObject->AddBaseComponent(new ScoreComponent(2000));


	SDL_Color colorHP{ 255,255,255 };
	auto fontHP = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
	auto hpObserver{ new HealthObserver({Transform(10,100,0),new TextComponent("HP: 20", fontHP, colorHP, false)},
		{Transform(100,100,0),new TextComponent("You Died: ", fontHP, colorHP, false)}) };

	auto scoreObserver{ new ScoreObserver({Transform(500,100,0),new TextComponent("Score: 0", fontHP, colorHP, false)}) };




	QBertObject->AddObeserver(hpObserver);
	QBertObject->AddObeserver(scoreObserver);
	scene.Add(QBertObject/*, true*/);



	SceneManager::GetInstance().AddPlayer(QBertObject);


	auto QBertObject2 = std::make_shared<GameObject>(100.f, 50.f, new TextureComponent("QBert/QbertCharachter.png", 0.25f));
	QBertObject2->AddBaseComponent(new QuitComponent());
	QBertObject2->AddBaseComponent(new PlayerMovement());
	QBertObject2->AddBaseComponent(new HealthComponent(20));
	QBertObject2->AddBaseComponent(new ScoreComponent(2000));

	auto hpObserver2{ new HealthObserver({Transform(10,150,0),new TextComponent("HP: 20", fontHP, colorHP, false)},
		{Transform(100,150,0),new TextComponent("You Died: ", fontHP, colorHP, false)}) };

	auto scoreObserver2{ new ScoreObserver({Transform(500,150,0),new TextComponent("Score: 0", fontHP, colorHP, false)}) };
	QBertObject2->AddObeserver(hpObserver2);
	QBertObject2->AddObeserver(scoreObserver2);


	scene.Add(QBertObject2/*, true*/);
	SceneManager::GetInstance().AddPlayer(QBertObject2);


}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		CreateDefaultCommandKeys(input);
		//auto& subject = Subject::GetInstance();


		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();
		//float lag{ 0.0f };
		const float msPerUpdate{ 40.f / 1000.f };//change this code under
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = duration<float>(currentTime - lastTime).count();

			lastTime = currentTime;
			//lag += deltaTime;

			ProcessInput(doContinue, sceneManager, input);




			//subject;
			sceneManager.Update(deltaTime);
			renderer.Render();



			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}

	}

	Cleanup();
}

void dae::Minigin::CreateUI() const
{
	//interface parts
	auto& renderer = Renderer::GetInstance();
	InterfacePart closeWindow{
	{"closeWindow",ImVec2{0,0}},
	{"" },
		{InterFaceNames::none }
	};
	
	InterfacePart BackToStartWindow{
	{"BackToStartScreen",ImVec2{0,0}},
	{"" },
		{InterFaceNames::start }
	};
	
	
	InterfacePart howToPlayPart{
		{"HowToPlay",ImVec2{0,0}},
		{"Hello!!!!" },
		{InterFaceNames::howToPlay }
	};
	InterfacePart ModesPart{
	{"Modes",ImVec2{0,0}},
	{"" },
	{InterFaceNames::modes }
	};
	InterfacePart HowTOplayPart{
		{Invalid_String,ImVec2{0,0}},
		{"Let Charachter Die: B button\nQuit game: Y Button\nGain Hp: X Button\n Lose Hp: A Button\n Move left: Left Button\nMove Right: Right Button\nMove Up: Up Button\nMove down: down Button\nMore Score: L1 Button\nLose Score:  R1 Button" },
		{InterFaceNames::none }
	};


	InterfacePart SinglePlayerButtonPart{
	{"1 player",ImVec2{0,0}},
	{"" },
	{InterFaceNames::modes }
	};
	InterfacePart TwoPlayerButtonPart{
	{"2 players",ImVec2{0,0}},
	{"" },
	{InterFaceNames::modes }
	};
	InterfacePart ThreePlayerButtonPart{
	{"3 players",ImVec2{0,0}},
	{"" },
	{InterFaceNames::modes }
	};
	InterfacePart FourPlayerButtonPart{
{"4 players",ImVec2{0,0}},
{"" },
	{InterFaceNames::modes }
	};
	//interface windows
	InterfaceWindow m_StartWindow("Startscreen", InterFaceNames::start);
	InterfaceWindow m_HowToPlayWindow("HowToPlay", InterFaceNames::howToPlay);
	InterfaceWindow m_ModesWindow("Modes", InterFaceNames::modes);
	
	m_StartWindow.AddInterfacePart(howToPlayPart);
	m_StartWindow.AddInterfacePart(ModesPart);
	m_StartWindow.AddInterfacePart(closeWindow);
	renderer.AddInterfaceWindow(m_StartWindow);
	
	m_ModesWindow.AddInterfacePart(SinglePlayerButtonPart);
	m_ModesWindow.AddInterfacePart(TwoPlayerButtonPart);
	m_ModesWindow.AddInterfacePart(ThreePlayerButtonPart);
	m_ModesWindow.AddInterfacePart(FourPlayerButtonPart);
	m_ModesWindow.AddInterfacePart(BackToStartWindow);
	m_ModesWindow.AddInterfacePart(closeWindow);
	renderer.AddInterfaceWindow(m_ModesWindow);

	m_HowToPlayWindow.AddInterfacePart(HowTOplayPart);
	m_HowToPlayWindow.AddInterfacePart(BackToStartWindow);
	m_HowToPlayWindow.AddInterfacePart(closeWindow);
	renderer.AddInterfaceWindow(m_HowToPlayWindow);
}


void dae::Minigin::ProcessInput(bool& doContinue, SceneManager& sceneMan, InputManager& inputman) 
{
	int index{ 0 };
	for (auto player : sceneMan.GetPlayers())//bad
	{
		std::vector<std::shared_ptr<Command>> commands{ inputman.ProcessInput(index) };// maybe change this
		
			for (std::shared_ptr<Command> pCommand: commands)
			{
				(*pCommand).Execute(player);
				
			}
		index++;
	}

	for (auto player : sceneMan.GetPlayers())
	{
		if (!player->GetComponent<QuitComponent>()->ContinueGame())
		{
			doContinue = player->GetComponent<QuitComponent>()->ContinueGame();
			return;
		}
	}
	
}




void dae::Minigin::CreateDefaultCommandKeys(InputManager& inputman)
{

	//default controls


	inputman.AddDefaultCommandAndKey({ std::make_shared<Die>(), OperateKey::keyStrokeUp, BButton });
	inputman.AddDefaultCommandAndKey({ std::make_shared<Quit>(), OperateKey::keyStrokeUp, YButton });
	inputman.AddDefaultCommandAndKey({ std::make_shared<MoveLeft>(), OperateKey::pressedDown, LeftButton });
	inputman.AddDefaultCommandAndKey({ std::make_shared<MoveRight>(), OperateKey::pressedDown, RightButton });
	inputman.AddDefaultCommandAndKey({ std::make_shared<MoveUp>(), OperateKey::pressedDown, UpButton });
	inputman.AddDefaultCommandAndKey({ std::make_shared<MoveDown>(), OperateKey::pressedDown, DownButton });
	inputman.AddDefaultCommandAndKey({ std::make_shared<GainHp>(), OperateKey::keyStrokeDown, XButton });
	inputman.AddDefaultCommandAndKey({ std::make_shared<LoseHp>(), OperateKey::keyStrokeDown, AButton });
	inputman.AddDefaultCommandAndKey({ std::make_shared<IncreaseScore>(), OperateKey::keyStrokeDown, L1Button });
	inputman.AddDefaultCommandAndKey({ std::make_shared<DecreaseScore>(), OperateKey::keyStrokeDown, R1Button });

}
