#include "MiniginPCH.h"
#include <iostream>
#include "QBertMap.h"
#include "GameObject.h"
#include "Scene.h"
#include "ComponentsHeaders.h"
#include "QBertComponentsHeaders.h"
#include <algorithm>



#include "QBertLevel.h"
#include "QbertTexturesComponent.h"




dae::QBertMap::QBertMap(int windowWidth, int windowHeight,const Level& levelInfo) :
	m_WindowWidth{ windowWidth }
	, m_WindowHeight{ windowHeight }
	, m_AmountOfCollums{ levelInfo.mapSizeColumns}
	, m_LeftFloatingDiscs(levelInfo.leftFloatingDiscs)
	, m_RightFloatingDiscs(levelInfo.rightFloatingDiscs)
	, m_FilePath("QBert")
	, m_PenaltyBlock(levelInfo.penaltyBlocks)

		
{
	m_DiskAdressName = m_FilePath + "/" + levelInfo.diskAdress + ".png";
	
	for (size_t i = 0; i < levelInfo.blockTextureAdressNames.size() ; ++i)
	{
		m_BlockFileNamesWithNickNames.push_back({ m_FilePath+ "/"+ levelInfo.blockTextureAdressNames[i]+".png", levelInfo.blockTextureNickNames[i] });
	}
	

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
			auto tmpBlockObject = std::make_shared<dae::GameObject>(posBlockX, posBlockY);
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
		element.second->AddPairComponent(new QbertTexturesComponent(2.f, m_BlockFileNamesWithNickNames), new MapBlockComponent(tmpPos.x, tmpPos.y, width, height, tmpVectorNames, m_PenaltyBlock));
	}






}

