#include "MiniginPCH.h"
#include <iostream>
#include "QBertMap.h"
#include "GameObject.h"
#include "Scene.h"
#include "ComponentsHeaders.h"
#include "QBertComponentsHeaders.h"
#include <algorithm>
#include <istream>
#include <fstream>

#include "QbertTexturesComponent.h"
#include "3rdPartyFiles/rapidjson/document.h"



dae::QBertMap::QBertMap(int windowWidth, int windowHeight) :
	m_WindowWidth{ windowWidth }
	, m_WindowHeight{ windowHeight }
	, m_AmountOfCollums{0}
	, m_LeftFloatingDiscs({})
	, m_RightFloatingDiscs({})
	, m_DiskAdressName()
	, m_FilePath("QBert")
{
	ReadFiles();
	//CreateTextures();
	CreateGameBlocks();
}

void dae::QBertMap::LoadMap(Scene& sceneMan)
{

	sceneMan.AddMap(m_UnMapBackgroundParts);

}


dae::GameObject* dae::QBertMap::GetFirstBlock()
{
	return m_UnMapBackgroundParts.find({ 6, 0 })->second.get();
}



void dae::QBertMap::ReadFiles()
{
	std::ifstream file{"Resources/LevelLayout/LevelOne.Json"};

	std::string getText{};
	std::string getTextCopy{};

	while (std::getline(file, getTextCopy))
	{
		getText += getTextCopy;
	}
	
	rapidjson::Reader testReader;
	rapidjson::Document document;
	
	document.Parse(getText.c_str());

	 m_AmountOfCollums = document["MapSizeColumns"].GetInt();

	 for (auto& v : document["LeftFloatingDiscs"].GetArray())
	 {
		 m_LeftFloatingDiscs.push_back(v.GetInt());
	 }
		
	 for (auto& v : document["RightFloatingDiscs"].GetArray())
	 {
		 m_RightFloatingDiscs.push_back(v.GetInt());
	 }



	 for (size_t i = 0; i < document["BlockTextureAdressNames"].GetArray().Size(); i++)
	 {

		 std::string tmpAdressName{ document["BlockTextureAdressNames"].GetArray()[i].GetString() };
		 m_BlockFileNamesWithNickNames.push_back({ m_FilePath +"/"+ tmpAdressName + ".png", document["BlockTextureNickNames"].GetArray()[i].GetString() });
	 }

	 m_DiskAdressName = m_FilePath + "/" + document["DiskName"].GetString() + ".png";
	
	
}


void dae::QBertMap::CreateGameDisks( int row, int collum,int currentRow, int maxRow, float posx, float posy, float width, float height)
{
	float posX{ posx };
	float posY{ posy- height/5 };
	if (row == 0)
	{
		for (int element : m_LeftFloatingDiscs)
		{
			if (element-1 == collum)
			{
				posX -= width/4;
				auto tmpBlockObject = std::make_shared<dae::GameObject>(posX, posY, std::shared_ptr<TextureComponent>( std::make_shared<TextureComponent>(m_DiskAdressName, 2.f)));
				tmpBlockObject->AddBaseComponent(new MapDiskComponent(posX, posY, width, height));
				m_UnMapBackgroundParts[{currentRow, element-2}] = tmpBlockObject;
				return;
			}
		}
	}
	else if (row == maxRow-1)
	{
		for (int element : m_RightFloatingDiscs)
		{
			if (element-1 == collum)
			{
				posX += (width - (width/3));
				auto tmpBlockObject = std::make_shared<dae::GameObject>(posX, posY, std::shared_ptr<TextureComponent>(std::make_shared<TextureComponent>("QBert/FloatingDisk.png", 2.f)));
				tmpBlockObject->AddBaseComponent(new MapDiskComponent(posX, posY,width, height ));
				m_UnMapBackgroundParts[{currentRow+1, element-2}] = tmpBlockObject;
				return;
				
			}
		}
	}
}


void dae::QBertMap::CreateGameBlocks()
{



	std::shared_ptr<TextureComponent>pTextureComp{ std::make_shared<TextureComponent>("QBert/BlueBlock.png", 2.f) };

	const int scale{ 2 };
	int maxBlocksRow{ 1 };


	const float width{ pTextureComp->GetWidth() };
	const float height{ pTextureComp->GetHeight() - 1.f };

	float posBlockX{ float(m_WindowWidth / 2) - (width / 2) };
	float posBlockY{ float(m_WindowHeight / 4) - (height / 2) };

	int row{ 6 };
	int collum{ 0 };


	for (int i = 0; i < m_AmountOfCollums; i++)
	{
		int tmpRow = row;
		for (int j = 0; j < maxBlocksRow; j++)
		{

			CreateGameDisks(j, i, tmpRow, maxBlocksRow, posBlockX, posBlockY, width, height);
			auto tmpBlockObject = std::make_shared<dae::GameObject>(posBlockX, posBlockY/*, m_PTextureComp*/);
			m_UnMapBackgroundParts[{tmpRow, collum}] = tmpBlockObject;
			//std::cout << tmpRow << " " << collum << "    ";

			posBlockX += width;
			tmpRow++;
		}
		//std::cout << "\n";
		collum++;

		row--;

		posBlockX -= (width * maxBlocksRow) + (width / 2);

		maxBlocksRow++;
		posBlockY += (height - height / 4);


	}





	std::vector<std::string> tmpVectorNames{};//CHANGE WHEN I PUT STUFF FROM FILES
	for (std::pair<std::string, std::string> element : m_BlockFileNamesWithNickNames)
	{
		tmpVectorNames.push_back(element.second);
	}


	for (auto element : m_UnMapBackgroundParts)
	{
		if (element.second->GetComponent<MapDiskComponent>())
		{
			continue;
		}
		auto tmpPos = element.second->GetPosition().GetPosition();
		element.second->AddPairComponent(new QbertTexturesComponent(2.f, m_BlockFileNamesWithNickNames), new MapBlockComponent(tmpPos.x, tmpPos.y, width, height, tmpVectorNames));
	}






}

