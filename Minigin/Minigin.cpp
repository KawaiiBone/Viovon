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

#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "QuitComponent.h"
#include "PlayerMovement.h"




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
	scene.Add(QBertObject/*, true*/);


	auto QBertObject2 = std::make_shared<GameObject>(100.f, 200.f, new TextureComponent("QBert/QbertCharachter.png", 0.25f));
	QBertObject2->AddComponent(new QuitComponent());
	QBertObject2->AddComponent(new PlayerMovement());
	scene.Add(QBertObject2/*, true*/);

	SceneManager::GetInstance().AddPlayer(QBertObject2);
	SceneManager::GetInstance().AddPlayer(QBertObject);
	

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
		CreateCommandKeys(input);

		

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

			
		
			

		
			renderer.Render();

			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	
	}

	Cleanup();
}





void dae::Minigin::ProcessInput(bool& doContinue, SceneManager& sceneMan, InputManager& inputman)
{
	for (auto player: sceneMan.GetPlayers())//bad
	{
		Command* command{ inputman.ProcessInput() };// maybe change this
		if (command)
		{
			command->Execute(player);
		}
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




void dae::Minigin::CreateCommandKeys(InputManager& inputman)
{
	//inputman.AddCommand({ new Crouch(XINPUT_GAMEPAD_X),false });
	//inputman.AddCommand({ new Fire(XINPUT_GAMEPAD_A),true });
	//inputman.AddCommand({ new Jump(XINPUT_GAMEPAD_B),false });
	//inputman.AddCommand({ new Quit(XINPUT_GAMEPAD_Y),true });


	inputman.AddCommandAndKey({ new Crouch(), OperateKey::keyStrokeDown, XINPUT_GAMEPAD_X });
	inputman.AddCommandAndKey({ new Fire(), OperateKey::keyStrokeDown, XINPUT_GAMEPAD_A });
	inputman.AddCommandAndKey({ new Die(), OperateKey::keyStrokeUp, XINPUT_GAMEPAD_B });
	inputman.AddCommandAndKey({ new Quit(), OperateKey::keyStrokeUp, XINPUT_GAMEPAD_Y });
	inputman.AddCommandAndKey({ new MoveLeft(), OperateKey::pressedDown, XINPUT_GAMEPAD_DPAD_LEFT });
	inputman.AddCommandAndKey({ new MoveRight(), OperateKey::pressedDown, XINPUT_GAMEPAD_DPAD_RIGHT });
	inputman.AddCommandAndKey({ new MoveUp(), OperateKey::pressedDown, XINPUT_GAMEPAD_DPAD_UP });
	inputman.AddCommandAndKey({ new MoveDown(), OperateKey::pressedDown, XINPUT_GAMEPAD_DPAD_DOWN });
	
}
