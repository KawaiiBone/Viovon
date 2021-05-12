#include "QBertMap.h"
#include "GameObject.h"
#include "Scene.h"
#include "ComponentsHeaders.h"
#include "QBertComponentsHeaders.h"
//#include "QbertTexturesComponent.h"


dae::QBertMap::QBertMap(int windowWidth, int windowHeight) :
	m_WindowWidth{ windowWidth }
	, m_WindowHeight{ windowHeight }
	, m_QbertSpawnPos{ 0,0,0 }
{

	CreateTextures();
	CreateGameBlocks();
}

void dae::QBertMap::LoadMap(Scene& sceneMan)
{
	for (std::pair<std::shared_ptr<GameObject>, AxialCoordinates> element : m_GameBlocks)
	{
		sceneMan.Add(element.first);
	}
}

dae::Transform dae::QBertMap::GetQbertSpawnPos()
{
	return m_QbertSpawnPos;
}

dae::GameObject* dae::QBertMap::GetFirstBlock()
{
	return m_GameBlocks[0].first.get();
}

void dae::QBertMap::CreateTextures()
{
	m_FileNamesWithNickNames.push_back({ "QBert/BlueBlock.png","BeginBlock" }); //READ FROM JSON FILE or from text
	m_FileNamesWithNickNames.push_back({ "QBert/YellowBlock.png", "MidBlock" });
//	m_FileNamesWithNickNames.push_back({ "QBert/PinkBlock.png", "EndBlock" });

}
void dae::QBertMap::CreateGameBlocks()
{

	// NEEDS COMPONENTS:
	// Something to trigger a different color
	//7
	//7
	std::shared_ptr<TextureComponent>pTextureComp{ std::make_shared<TextureComponent>("QBert/BlueBlock.png", 2.f) };
	
	const int scale{ 2 };
	size_t maxBlocksRow{ 1 };
	const size_t lenghtBlocksCollum{ 7 };


	const float width{ pTextureComp->GetWidth() };
	const float height{ pTextureComp->GetHeight() - 1.f };

	float posBlockX{ float(m_WindowWidth / 2) - (width / 2) };
	float posBlockY{ float(m_WindowHeight / 4) - (height / 2) };

	int row{ 6 };
	int collum{ 0 };


	for (size_t i = 0; i < lenghtBlocksCollum; i++)
	{
		int tmpRow = row;
		for (size_t j = 0; j < maxBlocksRow; j++)
		{


			auto tmpBlockObject = std::make_shared<dae::GameObject>(posBlockX, posBlockY/*, m_PTextureComp*/);
			//auto tmpBlockObject = std::make_shared<dae::GameObject>(posBlockX, posBlockY, m_PTextureComp);

			m_GameBlocks.push_back(std::pair<std::shared_ptr<GameObject>, AxialCoordinates>{tmpBlockObject, { tmpRow,collum }});
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


	
	for (std::pair<std::shared_ptr<GameObject>, AxialCoordinates> element : m_GameBlocks)
	{
		auto tmpPos = element.first->GetPosition().GetPosition();


		

		
		element.first->AddPairComponent( 
			new QbertTexturesComponent(2.f, m_FileNamesWithNickNames), 
			new BlockComponent(tmpPos.x + width / 4, tmpPos.y - height / 5, {}, tmpVectorNames, false) //ADD PARAMETERS
		);

		for (std::pair<std::shared_ptr<GameObject>, AxialCoordinates> tmpElement : m_GameBlocks)
		{
			if (element.second.row == tmpElement.second.row)
			{
				if (element.second.collum + 1 == tmpElement.second.collum)
				{

					element.first->GetComponent<BlockComponent>()->AddMovementPosBlock({ MovementQbert::RightDown, tmpElement.first.get() });

				}
				else if (element.second.collum - 1 == tmpElement.second.collum)
				{
					element.first->GetComponent<BlockComponent>()->AddMovementPosBlock({ MovementQbert::leftUp, tmpElement.first.get() });
				}
			}
			else if (element.second.row - 1 == tmpElement.second.row && element.second.collum + 1 == tmpElement.second.collum)
			{

				element.first->GetComponent<BlockComponent>()->AddMovementPosBlock({ MovementQbert::leftDown, tmpElement.first.get() });
			}
			else if (element.second.row + 1 == tmpElement.second.row && element.second.collum - 1 == tmpElement.second.collum)
			{
				element.first->GetComponent<BlockComponent>()->AddMovementPosBlock({ MovementQbert::rightUp, tmpElement.first.get() });
			}
		}
	}


	m_QbertSpawnPos = Transform{ m_GameBlocks[0].first->GetComponent<BlockComponent>()->GetPlatformPos().x,m_GameBlocks[0].first->GetComponent<BlockComponent>()->GetPlatformPos().y,0 };

}




