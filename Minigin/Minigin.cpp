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
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");



	
	auto backgroundObject = std::make_shared<GameObject>(0.f, 0.f, new TextureComponent( "background.jpg" ));
	scene.Add(backgroundObject/*, false*/);

	auto logoObject = std::make_shared<GameObject>(216.f, 180.f, new TextureComponent("logo.png"));
	scene.Add(logoObject/*, false*/);

	SDL_Color colorTitle{ 255,255,255 };
	auto fontTitle = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto daeTitleObject = std::make_shared<GameObject>(80.f,20.f, new TextComponent("Programming 4 Assignment", fontTitle, colorTitle, true));
	scene.Add(daeTitleObject/*, false*/);


	SDL_Color colorFps{ 255,0,0 };
	auto fontFps = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto FpsObject = std::make_shared<GameObject>(0.f, 10.f, new FPSComponent(),new TextComponent("FPS", fontFps, colorFps, false));
	scene.Add(FpsObject/*, false*/);



	
	auto QBertObject = std::make_shared<GameObject>(50.f, 50.f, new TextureComponent("QBert/QbertCharachter.png",0.25f));
	QBertObject->AddComponent(new QuitComponent());
	QBertObject->AddComponent(new PlayerMovement());
	QBertObject->AddComponent(new HealthComponent(20));
	QBertObject->AddComponent(new ScoreComponent(2000));
	

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
	QBertObject2->AddComponent(new QuitComponent());
	QBertObject2->AddComponent(new PlayerMovement());
	QBertObject2->AddComponent(new HealthComponent(20));
	QBertObject2->AddComponent(new ScoreComponent(2000));

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
		const float msPerUpdate{40.f/1000.f};//change this code under
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





void dae::Minigin::ProcessInput(bool& doContinue, SceneManager& sceneMan, InputManager& inputman)
{
	int index{ 0 };
	for (auto player: sceneMan.GetPlayers())//bad
	{
		std::shared_ptr<Command> command{ inputman.ProcessInput(index) };// maybe change this
		if (command)
		{
			(*command).Execute(player);
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
	//doContinue = sceneMan.GetPlayer()->GetComponent<QuitComponent>()->ContinueGame();
}




void dae::Minigin::CreateDefaultCommandKeys(InputManager& inputman)
{

	//default controls
	
	inputman.AddCommandAndKey({ std::make_shared<Die>(), OperateKey::keyStrokeUp, XINPUT_GAMEPAD_B });
	inputman.AddCommandAndKey({ std::make_shared<Quit>(), OperateKey::keyStrokeUp, XINPUT_GAMEPAD_Y });
	inputman.AddCommandAndKey({ std::make_shared<MoveLeft>(), OperateKey::pressedDown, XINPUT_GAMEPAD_DPAD_LEFT });
	inputman.AddCommandAndKey({ std::make_shared<MoveRight>(), OperateKey::pressedDown, XINPUT_GAMEPAD_DPAD_RIGHT });
	inputman.AddCommandAndKey({ std::make_shared<MoveUp>(), OperateKey::pressedDown, XINPUT_GAMEPAD_DPAD_UP });
	inputman.AddCommandAndKey({ std::make_shared<MoveDown>(), OperateKey::pressedDown, XINPUT_GAMEPAD_DPAD_DOWN });
	inputman.AddCommandAndKey({ std::make_shared<GainHp>(), OperateKey::keyStrokeDown, XINPUT_GAMEPAD_X });
	inputman.AddCommandAndKey({ std::make_shared<LoseHp>(), OperateKey::keyStrokeDown, XINPUT_GAMEPAD_A });
	inputman.AddCommandAndKey({ std::make_shared<IncreaseScore>(), OperateKey::keyStrokeDown, XINPUT_GAMEPAD_LEFT_SHOULDER });
	inputman.AddCommandAndKey({ std::make_shared<DecreaseScore>(), OperateKey::keyStrokeDown, XINPUT_GAMEPAD_RIGHT_SHOULDER });
	
}
