#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "QbertTexturesComponent.h"
#include "Transform.h"

namespace dae
{
	struct MovementPosBlock;
	struct AxialCoordinates
	{
		int row;
		int collum;
	};
	
	class Scene;
	class GameObject;
	class TextureComponent;
	class QBertMap
	{
	public:
		QBertMap(int windowWidth,int windowHeight);
		void LoadMap(Scene& sceneMan);
		Transform GetQbertSpawnPos();
		GameObject* GetFirstBlock();
	private:
		void CreateGameBlocks();
		void CreateTextures();

		//std::pair<std::vector<GameObject>, std::vector<GameObject>> m_GameBlocks;
		
		std::vector < std::pair< std::shared_ptr<GameObject>, AxialCoordinates>> m_GameBlocks;
		const int m_WindowWidth;
		const int m_WindowHeight;
		Transform m_QbertSpawnPos;
		std::vector<std::pair<std::string, std::string>> m_FileNamesWithNickNames;

	};
}
