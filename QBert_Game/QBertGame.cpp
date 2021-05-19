#include "QBertGame.h"
#include "Command.h"
#include "GameObject.h"
#include "Scene.h"


#include "InputManager.h"

#include "QBertCommands.h"
#include "QbertTexturesComponent.h"
#include <istream>
#include <fstream>
#include "3rdPartyFiles/rapidjson/document.h"

dae::QBertGame::QBertGame(int windowWidth, int windowHeight) :
	m_Menu(TypeOfScene::startMenu), m_AmountOfLevels{3}, m_QBertPlayerOne(0), m_QBertPlayerTwo(1)
	
{

	
	TypeOfScene tmpTypeScene{ TypeOfScene::level1 };
	
	for (int i = 1; i < m_AmountOfLevels+1; ++i)
	{
		m_Levels.push_back({ tmpTypeScene, windowWidth, windowHeight, ReadLevelFile(i) });
		tmpTypeScene = static_cast<TypeOfScene>(static_cast<int>(tmpTypeScene) + 1);
	}
}

void dae::QBertGame::LoadQbertGame()
{
	m_QBertPlayerOne.CreateQbert();
	m_Menu.CreateMenu();
	for (auto element : m_Levels)
	{
		element.CreateLevel();
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

dae::Level dae::QBertGame::ReadLevelFile(int index)
{
	std::ifstream file{ "Resources/LevelLayout/Levels.Json" };

	std::string getText{};
	std::string getTextCopy{};

	while (std::getline(file, getTextCopy))
	{
		getText += getTextCopy;
	}

	rapidjson::Reader testReader;
	rapidjson::Document document;

	document.Parse(getText.c_str());

	Level tmpStructLevel;
	std::string levelName{ "Level"+ std::to_string(index) };




	
	const auto& lvlDocumentArray = document[levelName.c_str()];



	tmpStructLevel.mapSizeColumns = lvlDocumentArray["MapSizeColumns"].GetInt();

	for (auto& element : lvlDocumentArray["LeftFloatingDiscs"].GetArray())
	{
		tmpStructLevel.leftFloatingDiscs.push_back(element.GetInt());
	}


	for (auto& element : lvlDocumentArray["RightFloatingDiscs"].GetArray())
	{
		tmpStructLevel.rightFloatingDiscs.push_back(element.GetInt());
	}

	for (auto& element : lvlDocumentArray["BlockTextureAdressNames"].GetArray())
	{
		tmpStructLevel.blockTextureAdressNames.push_back(element.GetString());
	}


	for (auto& element : lvlDocumentArray["BlockTextureNickNames"].GetArray())
	{
		tmpStructLevel.blockTextureNickNames.push_back(element.GetString());
	}


	tmpStructLevel.diskAdress = lvlDocumentArray["DiskName"].GetString();

	tmpStructLevel.coilySpawn = lvlDocumentArray["CoilySpawn"].GetBool();

	tmpStructLevel.coilySpawnTime = lvlDocumentArray["CoilySpawnTime"].GetFloat();

	for (auto& element : lvlDocumentArray["UggAbdWrongwaySpawnTimes"].GetArray())
	{
		tmpStructLevel.uggAbdWrongwaySpawnTimes.push_back(element.GetFloat());
	}

	for (auto& element : lvlDocumentArray["SlickAndSamSpawnTimes"].GetArray())
	{
		tmpStructLevel.slickAndSamSpawnTimes.push_back(element.GetFloat());
	}

	tmpStructLevel.penaltyBlocks = lvlDocumentArray["PenaltyBlocks"].GetBool();
	return tmpStructLevel;
}
