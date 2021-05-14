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
	, m_QbertSpawnPos{ 0,0,0 }
	, m_PlatformPenalty{false}
	, m_AmountOfCollums{0}
	, m_LeftFloatingDiscs({})
	, m_RightFloatingDiscs({})
{
	ReadFiles();
	//CreateTextures();
	CreateGameBlocks();
}

void dae::QBertMap::LoadMap(Scene& sceneMan)
{

	sceneMan.AddMap(m_UnMapBackgroundParts);
	
	/*for (std::pair<std::shared_ptr<GameObject>, AxialCoordinates> element : m_GameBlocks)
	{
		sceneMan.Add(element.first);
	}
	for (auto element : m_GameRightDisks)
	{
		sceneMan.Add(element.first);
	}
	for (auto element : m_GameLeftDisks)
	{
		sceneMan.Add(element.first);
	}*/
}

dae::Transform dae::QBertMap::GetQbertSpawnPos()
{
	return m_QbertSpawnPos;
}

dae::GameObject* dae::QBertMap::GetFirstBlock()
{
	return m_UnMapBackgroundParts.find({ 6, 0 })->second.get();
}

std::pair<dae::GameObject*, dae::GameObject*> dae::QBertMap::GetVersusBlocks()
{
	return { m_GameBlocks[20].first.get(),m_GameBlocks.back().first.get() };//CHANGE SOON
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

	
	 m_PlatformPenalty = document["PenaltyPlatforms"].GetBool();


	 for (size_t i = 0; i < document["TextureAdressName"].GetArray().Size(); i++)
	 {

		 std::string tmpAdressName{ document["TextureAdressName"].GetArray()[i].GetString() };
		 m_FileNamesWithNickNames.push_back({ "QBert/"+ tmpAdressName + ".png", document["TextureNickName"].GetArray()[i].GetString() });
	 }


	
	
}

void dae::QBertMap::CreateTextures()
{
	m_FileNamesWithNickNames.push_back({ "QBert/BlueBlock.png","BeginBlock" }); //READ FROM JSON FILE or from text
	m_FileNamesWithNickNames.push_back({ "QBert/YellowBlock.png", "MidBlock" });
//	m_FileNamesWithNickNames.push_back({ "QBert/PinkBlock.png", "EndBlock" });

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
				auto tmpBlockObject = std::make_shared<dae::GameObject>(posX, posY, std::shared_ptr<TextureComponent>( std::make_shared<TextureComponent>("QBert/FloatingDisk.png", 2.f)));
				//m_GameLeftDisks.push_back({ tmpBlockObject, collum });
				tmpBlockObject->AddBaseComponent(new MapDiskComponent(posX, posY));
				m_UnMapBackgroundParts[{currentRow, element-2}] = tmpBlockObject;
				//std::cout << "\n leftDisk: " << currentRow << "  " << element -2 << "\n";
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
				tmpBlockObject->AddBaseComponent(new MapDiskComponent(posX, posY));
				//auto tmpBlockObject = std::make_shared<dae::GameObject>(posX, posY);
				//m_GameRightDisks.push_back({ tmpBlockObject, collum });
				m_UnMapBackgroundParts[{currentRow+1, element-2}] = tmpBlockObject;
				//std::cout << "\n rightDisk: " << currentRow << "  " << element << "\n";
				return;
				
			}
		}
	}
}

void dae::QBertMap::FinishGameDisks()
{
	//std::vector<MovementPosBlock> tmpVec{ MovementPosBlock {MovementQbert::none,GetFirstBlock()} };
	std::vector<std::string> tmpVecString{ "0" };
	
	for (auto element : m_GameRightDisks)
	{
		auto pos{ element.first->GetPosition().GetPosition() };
		//element.first->AddBaseComponent(new MapDiskComponent(pos.x/3, pos.y/4, tmpVec, {}));
	}
	for (auto element : m_GameLeftDisks)
	{
		auto pos{ element.first->GetPosition().GetPosition() };
		//element.first->AddBaseComponent(new MapDiskComponent(pos.x / 3, pos.y / 4, tmpVec, {}));
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
		
			
			
			//m_GameBlocks.push_back(std::pair<std::shared_ptr<GameObject>, AxialCoordinates>{tmpBlockObject, { tmpRow,collum }});
			std::cout << tmpRow << " " << collum << "    ";

			posBlockX += width;
			tmpRow++;
		}
		std::cout << "\n";
		collum++;

		row--;

		posBlockX -= (width * maxBlocksRow) + (width / 2);

		maxBlocksRow++;
		posBlockY += (height - height / 4);


	}




	
	std::vector<std::string> tmpVectorNames{};//CHANGE WHEN I PUT STUFF FROM FILES
	for (std::pair<std::string, std::string> element : m_FileNamesWithNickNames)
	{
		tmpVectorNames.push_back(element.second);
	}


	for (auto  element : m_UnMapBackgroundParts)
	{
		if (element.second->GetComponent<MapDiskComponent>())
		{
			continue;
		}
		auto tmpPos = element.second->GetPosition().GetPosition();
		element.second->AddPairComponent(new QbertTexturesComponent(2.f, m_FileNamesWithNickNames), new MapBlockComponent(tmpPos.x + width / 4, tmpPos.y - height / 5, tmpVectorNames, m_PlatformPenalty));
	}





	
	
	/*for (std::pair<std::shared_ptr<GameObject>, AxialCoordinates> element : m_GameBlocks)
	{
		auto tmpPos = element.first->GetPosition().GetPosition();


		bool hasRighUp{ false };
		bool hasLeftUp{ false };
		
		element.first->AddPairComponent(new QbertTexturesComponent(2.f, m_FileNamesWithNickNames), new MapBlockComponent(tmpPos.x + width / 4, tmpPos.y - height / 5, {}, tmpVectorNames, m_PlatformPenalty));//ADD PARAMETERS);

		for (std::pair<std::shared_ptr<GameObject>, AxialCoordinates> tmpElement : m_GameBlocks)
		{
			if (element.second.row == tmpElement.second.row)
			{
				if (element.second.collum + 1 == tmpElement.second.collum)
				{
					element.first->GetComponent<MapPartComponent>()->AddMovementPosBlock({ MovementQbert::RightDown, tmpElement.first.get() });
					//element.first->GetComponent<MapBlockComponent>()->AddMovementPosBlock({ MovementQbert::RightDown, tmpElement.first.get() });

				}
				else if (element.second.collum - 1 == tmpElement.second.collum)
				{
					element.first->GetComponent<MapPartComponent>()->AddMovementPosBlock({ MovementQbert::leftUp, tmpElement.first.get() });
					//element.first->GetComponent<MapBlockComponent>()->AddMovementPosBlock({ MovementQbert::leftUp, tmpElement.first.get() });
					hasLeftUp = true;
				}
			}
			else if (element.second.row - 1 == tmpElement.second.row && element.second.collum + 1 == tmpElement.second.collum)
			{

				element.first->GetComponent<MapPartComponent>()->AddMovementPosBlock({ MovementQbert::leftDown, tmpElement.first.get() });
				//element.first->GetComponent<MapBlockComponent>()->AddMovementPosBlock({ MovementQbert::leftDown, tmpElement.first.get() });
			}
			else if (element.second.row + 1 == tmpElement.second.row && element.second.collum - 1 == tmpElement.second.collum)
			{
				element.first->GetComponent<MapPartComponent>()->AddMovementPosBlock({ MovementQbert::rightUp, tmpElement.first.get() });
				//element.first->GetComponent<MapBlockComponent>()->AddMovementPosBlock({ MovementQbert::rightUp, tmpElement.first.get() });
				hasRighUp = true;
			}

		}


		if (!hasLeftUp )
		{
			for (std::pair<std::shared_ptr<GameObject>, int> elementDisks : m_GameLeftDisks)
			{
				if (elementDisks.second == element.second.collum)
				{
					element.first->GetComponent<MapPartComponent>()->AddMovementPosBlock({ MovementQbert::leftUp, elementDisks.first.get() });
					/*break;*/
		/*		}
			}
		}
		else if(!hasRighUp)
		{
			for (std::pair<std::shared_ptr<GameObject>, int> elementDisks : m_GameRightDisks)
			{
				if (elementDisks.second == element.second.collum)
				{
					element.first->GetComponent<MapPartComponent>()->AddMovementPosBlock({ MovementQbert::rightUp, elementDisks.first.get() });
				/*	break;*/
			/*	}
			}
	/*	}
		

		
		
	}


	m_QbertSpawnPos = Transform{ m_GameBlocks[0].first->GetComponent<MapPartComponent>()->GetPlatformPos().x,m_GameBlocks[0].first->GetComponent<MapPartComponent>()->GetPlatformPos().y,0 };
	FinishGameDisks();
	//m_QbertSpawnPos = Transform{ m_GameBlocks[0].first->GetComponent<MapBlockComponent>()->GetPlatformPos().x,m_GameBlocks[0].first->GetComponent<MapBlockComponent>()->GetPlatformPos().y,0 };
	*/
}




