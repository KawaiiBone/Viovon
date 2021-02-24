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

	SceneManager::GetInstance().SetPlayer(QBertObject);

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

			Command* command{ input.ProcessInput() };
			if (command)
			{
				command->Execute(sceneManager.GetPlayer());
			}
			//doContinue = input.ProcessInput();
			doContinue = sceneManager.GetPlayer()->GetComponent<QuitComponent>()->ContinueGame();

			sceneManager.GetPlayer()->GetComponent<PlayerMovement>()->MoveLeft();
			sceneManager.Update(deltaTime);
		
			

		
			renderer.Render();

			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	
	}

	Cleanup();
}

void dae::Minigin::CreateCommandKeys(InputManager& inputman)
{
	inputman.AddCommand({ new Crouch(XINPUT_GAMEPAD_X),false });
	inputman.AddCommand({ new Fire(XINPUT_GAMEPAD_A),true });
	inputman.AddCommand({ new Jump(XINPUT_GAMEPAD_B),false });
	inputman.AddCommand({ new Quit(XINPUT_GAMEPAD_Y),true });
	inputman.AddCommand({ new MoveRight(XINPUT_GAMEPAD_DPAD_RIGHT),false });
	inputman.AddCommand({ new MoveLeft(XINPUT_GAMEPAD_DPAD_LEFT),false });
	
}
