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
#include <istream>
#include <fstream>

dae::QBertMenu::QBertMenu(TypeOfScene typeScene) :
	m_TypeScene(typeScene),
	m_HowToPlayString{""}
{
	CreateHowToPlayString();

}

void dae::QBertMenu::CreateMenu(QBert& qbertP2, CoilyPlayer& coilyP2)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene(m_TypeScene);
	CreateMenuObjects(scene);
	auto& renderer = Renderer::GetInstance();
	
	InterfacePart playModes{	{"Play modes",ImVec2{0,0}},	{"" },	{InterFaceNames::modes },	};	
	playModes.myFunctionWrapper = []() -> void{};
	
	InterfacePart goToControllers{{"Controller Options",ImVec2{0,0}},{"" },{InterFaceNames::controller },	};
	goToControllers.myFunctionWrapper = []() -> void{};
	
	InterfacePart goToHowToplayPart{{"How to play",ImVec2{0,0}},{"" },	{InterFaceNames::howToPlay },};
	goToHowToplayPart.myFunctionWrapper = []() -> void{};

	InterfacePart BackToStartWindow{{"BackToStartScreen",ImVec2{0,0}},{"" },	{InterFaceNames::start }};
	BackToStartWindow.myFunctionWrapper = []() -> void{	};

	InterfacePart singlePlayer{{"SinglePlayer",ImVec2{0,0}},{"" },	{InterFaceNames::play }	};
	singlePlayer.myFunctionWrapper = []() -> void	{SceneManager::GetInstance().SetGameMode(GameMode::singleplayer);};

	InterfacePart coop{{"Co-op",ImVec2{0,0}},{"" },	{InterFaceNames::play }	};
	coop.myFunctionWrapper = [&]() -> void	{	qbertP2.CreateQbert();		SceneManager::GetInstance().SetGameMode(GameMode::coop);};

	InterfacePart versus{{"Versus",ImVec2{0,0}},{"" },	{InterFaceNames::play }	};
	versus.myFunctionWrapper = [&]() -> void	{	coilyP2.CreateCoily();		SceneManager::GetInstance().SetGameMode(GameMode::versus);};

	InterfacePart controllerOption1{{"Player 1 uses keyboard",ImVec2{0,0}},{"" },	{InterFaceNames::start }	};
	controllerOption1.myFunctionWrapper = []()	{auto& input = InputManager::GetInstance();	input.SetPLayerUsesKeyboard(true);	};
	
	InterfacePart controllerOption2{{"Player 1 uses controller",ImVec2{0,0}},{"" },	{InterFaceNames::start }	};
	controllerOption2.myFunctionWrapper = []()	{		auto& input = InputManager::GetInstance();		input.SetPLayerUsesKeyboard(false);	};
	
	InterfacePart infoHowtoPlay{{"",ImVec2{0,0}},		{m_HowToPlayString },	{InterFaceNames::none }	};
	
	InterfacePart demo{{"Demo",ImVec2{0,0}},{"" },	{InterFaceNames::play }	};
	demo.myFunctionWrapper = [](){		SceneManager::GetInstance().ChangeScene(TypeOfScene::demo);	};
	
	InterfacePart startPlayPart{{"Play",ImVec2{0,0}},{"" },	{InterFaceNames::start }	};
	startPlayPart.myFunctionWrapper = []()	{		SceneManager::GetInstance().ChangeScene(TypeOfScene::level1);	};

	InterfacePart selectLevel{{"Select Level",ImVec2{0,0}},{"" },	{InterFaceNames::selectedLevel }	};
	selectLevel.myFunctionWrapper = []()	{	};

	InterfacePart levelOne{{"Level 1",ImVec2{0,0}},{"" },	{InterFaceNames::selectedLevel }	};
	levelOne.myFunctionWrapper = []()	{		SceneManager::GetInstance().ChangeScene(TypeOfScene::level1);	};

	InterfacePart levelTwo{{"Level 2",ImVec2{0,0}},{"" },	{InterFaceNames::selectedLevel }	};
	levelTwo.myFunctionWrapper = []()	{		SceneManager::GetInstance().ChangeScene(TypeOfScene::level2);	};

	InterfacePart levelThree{{"Level 3",ImVec2{0,0}},{"" },	{InterFaceNames::selectedLevel }	};
	levelThree.myFunctionWrapper = []()	{		SceneManager::GetInstance().ChangeScene(TypeOfScene::level3);	};
	
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
	
	InterfaceWindow selectLevelMenu{ "controller options",InterFaceNames::selectedLevel };
	selectLevelMenu.AddInterfacePart(levelOne);
	selectLevelMenu.AddInterfacePart(levelTwo);
	selectLevelMenu.AddInterfacePart(levelThree);
	
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

void dae::QBertMenu::CreateHowToPlayString()
{
	
	std::ifstream file{ "../Data/LevelLayout/HowToPLayInfo.txt" };
	std::string fileLine{};
	while (std::getline(file, fileLine))
	{
		m_HowToPlayString += fileLine + "\n";
	}
}
