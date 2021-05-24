#include "QBertMenu.h"
#include <functional>

#include "FPSComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "QBert.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Subject.h"
#include "TextComponent.h"
#include "CoilyPlayer.h"

dae::QBertMenu::QBertMenu(TypeOfScene typeScene) :
	m_TypeScene(typeScene)
{


}

void dae::QBertMenu::CreateMenu(QBert& qbertP2, CoilyPlayer& coilyP2)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene(m_TypeScene);
	CreateMenuObjects(scene);
	auto& renderer = Renderer::GetInstance();
	InterfacePart playModes{
	{"Play modes",ImVec2{0,0}},
	{"" },
	{InterFaceNames::modes },

	};
	playModes.myFunctionWrapper = []() -> void
	{
		std::cout << "Going to modes! " << std::endl;

	};
	InterfacePart goToControllers{
{"Controller Options",ImVec2{0,0}},
{"" },
{InterFaceNames::controller },

	};
	goToControllers.myFunctionWrapper = []() -> void
	{
		std::cout << "Going to Controllers! " << std::endl;

	};
	InterfacePart goToHowToplayPart{
{"How to play",ImVec2{0,0}},
{"" },
	{InterFaceNames::howToPlay },

	};
	goToHowToplayPart.myFunctionWrapper = []() -> void
	{
		std::cout << "Going to How To play! " << std::endl;

	};

	InterfacePart BackToStartWindow{
{"BackToStartScreen",ImVec2{0,0}},
{"" },
	{InterFaceNames::start }
	};
	BackToStartWindow.myFunctionWrapper = []() -> void
	{
		std::cout << "Going back to star screen! " << std::endl;

	};


	InterfacePart singlePlayer{
{"SinglePlayer",ImVec2{0,0}},
{"" },
	{InterFaceNames::play }
	};
	singlePlayer.myFunctionWrapper = []() -> void
	{
		SceneManager::GetInstance().SetGameMode(GameMode::singleplayer);
		std::cout << "You choose singleplayer! " << std::endl;

	};

	InterfacePart coop{
{"Co-op",ImVec2{0,0}},
{"" },
	{InterFaceNames::play }
	};
	coop.myFunctionWrapper = [&]() -> void
	{
		qbertP2.CreateQbert();
		SceneManager::GetInstance().SetGameMode(GameMode::coop);
		std::cout << "You choose Co-op! " << std::endl;

	};

	InterfacePart versus{
{"Versus",ImVec2{0,0}},
{"" },
	{InterFaceNames::play }
	};
	versus.myFunctionWrapper = [&]() -> void
	{
		coilyP2.CreateCoily();
		SceneManager::GetInstance().SetGameMode(GameMode::versus);
		std::cout << "You choose Versus! " << std::endl;

	};


	InterfacePart controllerOption1{
{"Player 1 uses keyboard",ImVec2{0,0}},
{"" },
	{InterFaceNames::start }
	};
	controllerOption1.myFunctionWrapper = []()
	{
		auto& input = InputManager::GetInstance();
		input.SetPLayerUsesKeyboard(true);
		std::cout << "You choose Player 1 uses keyboard! " << std::endl;
	};
	
	InterfacePart controllerOption2{
{"Player 1 uses controller",ImVec2{0,0}},
{"" },
	{InterFaceNames::start }
	};
	controllerOption2.myFunctionWrapper = []()
	{
		auto& input = InputManager::GetInstance();
		input.SetPLayerUsesKeyboard(false);
		std::cout << "You choose Player 1 uses controller! " << std::endl;
	};
	
	InterfacePart infoHowtoPlay{
{"",ImVec2{0,0}},
{"Quit game: Y/Escape \nMove left down: Left Button/A/Left Arrow\nMove Right up: Right Button/D/Right Arrow\nMove left Up: Up Button/W/Arrow Up\nMove right down: down Button/S/Arrow Down" },
	{InterFaceNames::none }
	};
	
	InterfacePart demo{
{"Demo",ImVec2{0,0}},
{"" },
	{InterFaceNames::play }
	};
	demo.myFunctionWrapper = []()
	{
		SceneManager::GetInstance().ChangeScene(TypeOfScene::demo);
		std::cout << "You choose Demo! " << std::endl;
	};
	
	InterfacePart startPlayPart{
{"Play",ImVec2{0,0}},
{"" },
	{InterFaceNames::start }
	};
	startPlayPart.myFunctionWrapper = []()
	{
		SceneManager::GetInstance().ChangeScene(TypeOfScene::level1);
		std::cout << "You choose Play! " << std::endl;
	};

	InterfacePart selectLevel{
{"Select Level",ImVec2{0,0}},
{"" },
	{InterFaceNames::selectedLevel }
	};
	selectLevel.myFunctionWrapper = []()
	{
		
		std::cout << "You choose selecting a level! " << std::endl;
	};

	InterfacePart levelOne{
{"Level 1",ImVec2{0,0}},
{"" },
	{InterFaceNames::selectedLevel }
	};
	levelOne.myFunctionWrapper = []()
	{
		SceneManager::GetInstance().ChangeScene(TypeOfScene::level1);
		std::cout << "You choose to Play Level 1! " << std::endl;
	};

	InterfacePart levelTwo{
{"Level 2",ImVec2{0,0}},
{"" },
	{InterFaceNames::selectedLevel }
	};
	levelTwo.myFunctionWrapper = []()
	{
		SceneManager::GetInstance().ChangeScene(TypeOfScene::level2);
		std::cout << "You choose to Play Level 2! " << std::endl;
	};

	InterfacePart levelThree{
{"Level 3",ImVec2{0,0}},
{"" },
	{InterFaceNames::selectedLevel }
	};
	levelThree.myFunctionWrapper = []()
	{
		SceneManager::GetInstance().ChangeScene(TypeOfScene::level3);
		std::cout << "You choose to Play Level 3! " << std::endl;
	};
	
	InterfaceWindow startMenu{ "Start menu",InterFaceNames::start };
	startMenu.AddInterfacePart(playModes);
	startMenu.AddInterfacePart(goToControllers);
	startMenu.AddInterfacePart(goToHowToplayPart);

	InterfaceWindow modesMenu{ "Modes menu",InterFaceNames::modes };
	modesMenu.AddInterfacePart(singlePlayer);
	modesMenu.AddInterfacePart(coop);
	modesMenu.AddInterfacePart(versus);
	modesMenu.AddInterfacePart(BackToStartWindow);

	InterfaceWindow howToPlayMenu{ "how to play menu",InterFaceNames::howToPlay };
	howToPlayMenu.AddInterfacePart(infoHowtoPlay);
	howToPlayMenu.AddInterfacePart(BackToStartWindow);

	InterfaceWindow controllerOptions{ "controller options",InterFaceNames::controller };
	controllerOptions.AddInterfacePart(controllerOption1);
	controllerOptions.AddInterfacePart(controllerOption2);
	controllerOptions.AddInterfacePart(BackToStartWindow);

	InterfaceWindow playMenu{ "controller options",InterFaceNames::play };
	playMenu.AddInterfacePart(startPlayPart);
	playMenu.AddInterfacePart(selectLevel);
	//playMenu.AddInterfacePart(BackToStartWindow);
	
	InterfaceWindow selectLevelMenu{ "controller options",InterFaceNames::selectedLevel };
	selectLevelMenu.AddInterfacePart(levelOne);
	selectLevelMenu.AddInterfacePart(levelTwo);
	selectLevelMenu.AddInterfacePart(levelThree);
	//selectLevelMenu.AddInterfacePart(BackToStartWindow);
	
	renderer.AddInterfaceWindow(startMenu);
	renderer.AddInterfaceWindow(modesMenu);
	renderer.AddInterfaceWindow(howToPlayMenu);
	renderer.AddInterfaceWindow(playMenu);
	renderer.AddInterfaceWindow(selectLevelMenu);
	renderer.AddInterfaceWindow(controllerOptions);


}

void dae::QBertMenu::CreateMenuObjects(Scene& scene)
{
	auto backgroundObject = std::make_shared<dae::GameObject>(0.f, 0.f, std::make_shared<TextureComponent>("background.jpg"));
	scene.AddBackground(backgroundObject/*, false*/);

	auto logoObject = std::make_shared<dae::GameObject>(216.f, 80.f, std::make_shared<TextureComponent>("logo.png"));
	scene.AddBackground(logoObject/*, false*/);

	SDL_Color colorFps{ 255,0,0 };
	auto fontFps = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto FpsObject = std::make_shared<dae::GameObject>(0.f, 10.f);
	FpsObject->AddPairComponent(new dae::TextComponent("FPS", fontFps, colorFps, false), new dae::FPSComponent());
	scene.Add(FpsObject/*, false*/);
}
