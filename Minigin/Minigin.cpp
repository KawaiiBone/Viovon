#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>


#include "audio.h"
#include "Command.h"
#include "GameObject.h"
#include "Scene.h"


#include "ComponentsHeaders.h"
#include "ObserversHeaders.h"
#include "InterfaceWindow.h"

#include "ServiceLocater.h"





using namespace std;
using namespace std::chrono;

dae::Minigin::Minigin()
{
	Initialize();
	ResourceManager::GetInstance().Init("../Data/");//stays
	ServiceLocater::RegisterSoundSystem(new SoundSystem());//makes sound

}

void dae::Minigin::Initialize()
{
	_putenv("SDL_AUDIODRIVER=DirectSound");//fix for audio
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	
	initAudio();//for audio
	
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



	AddPlayers(scene, 4);



}

void dae::Minigin::Cleanup()
{
	ServiceLocater::CleanUp();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	endAudio();
	SDL_Quit();
}

void dae::Minigin::Run()
{

	//Initialize();
	//ServiceLocater::RegisterSoundSystem(new SoundSystem());//makes sound
	//ServiceLocater::GetSoundSystem().PlaySound("../Data/sounds/door1.wav", 50);//test
	//ServiceLocater::GetSoundSystem().PlaySound("../Data/sounds/door1.wav", 50);
	//ServiceLocater::GetSoundSystem().PlayMusic("../Data/music/highlands.wav", 100);
	//// tell the resource manager where he can find the game data
	///
	//LoadGame();
	//
	//ResourceManager::GetInstance().Init("../Data/");
	//ServiceLocater::RegisterSoundSystem(new SoundSystem());//makes sound

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

		for (std::shared_ptr<Command> pCommand : commands)
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
	inputman.AddDefaultCommandAndKey({ std::make_shared<GainLife>(), OperateKey::keyStrokeDown, XButton });
	inputman.AddDefaultCommandAndKey({ std::make_shared<LoseLife>(), OperateKey::keyStrokeDown, AButton });
	inputman.AddDefaultCommandAndKey({ std::make_shared<IncreaseScore>(), OperateKey::keyStrokeDown, L1Button });
	inputman.AddDefaultCommandAndKey({ std::make_shared<DecreaseScore>(), OperateKey::keyStrokeDown, R1Button });

}

void dae::Minigin::AddPlayers(Scene& sceneMan, int totalPlayers) const
{
	const int maxPlayers{ 4 };
	if (totalPlayers > maxPlayers)
	{
		totalPlayers = maxPlayers;
	}
	else if (totalPlayers < 1)
	{
		totalPlayers = 1;
	}



	ImVec2 posPlayer{50,50};
	ImVec2 posHealthObserver{10,100};
	ImVec2 posDeadObserver{100,100};
	ImVec2 posScoreObserver{500,100};

	const float playerSpace{ 100.f };
	const float textSpace{ 25.f };

	for (int i = 0; i < totalPlayers; i++)
	{
		SDL_Color colorHP{ 255,255,255 };
		auto fontHP = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
		auto livesObserver{ new LivesObserver({posHealthObserver.x,posHealthObserver.y,new TextComponent("Lives: 20", fontHP, colorHP, false)},
			{posDeadObserver.x,posDeadObserver.y,new TextComponent("You Died: ", fontHP, colorHP, false)}) };

		auto scoreObserver{ new ScoreObserver({posScoreObserver.x,posScoreObserver.y,new TextComponent("Score: 0", fontHP, colorHP, false)}) };

		
		auto hpComponent{ new LivesComponent(20) };
		auto scoreComponent{ new ScoreComponent(2000) };

		hpComponent->AddObserver(livesObserver);
		scoreComponent->AddObserver(scoreObserver);

		
		auto QBertObject = std::make_shared<GameObject>(posPlayer.x, posPlayer.y, new TextureComponent("QBert/QbertCharachter.png", 0.25f));
		QBertObject->AddBaseComponent(new QuitComponent());
		QBertObject->AddBaseComponent(new PlayerMovement());
		QBertObject->AddBaseComponent(hpComponent);
		QBertObject->AddBaseComponent(scoreComponent);




		sceneMan.Add(QBertObject);
		SceneManager::GetInstance().AddPlayer(QBertObject);

		posPlayer.y += playerSpace/2;
		posPlayer.x += playerSpace;
		posHealthObserver.y += textSpace;
		posDeadObserver.y += textSpace;
		posScoreObserver.y += textSpace;
		
	}
}
