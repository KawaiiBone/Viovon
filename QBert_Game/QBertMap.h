﻿#pragma once
#include <vector>
#include <memory>
#include <iostream>
//#include "QbertTexturesComponent.h"
#include <unordered_map>

#include "Transform.h"
#include "3rdPartyFiles/rapidjson/rapidjson.h"
//#include "Scene.h"
//#include <unordered_map>

namespace dae
{
	
	struct MovementPosBlock;
	
	struct AxialCoordinates
	{
		int row;
		int collum;

		bool operator==(const AxialCoordinates& other) const
		{
			return (row == other.row
				&& collum == other.collum);
		}

		bool operator!=(const AxialCoordinates& other) const
		{
			return (row != other.row
				|| collum != other.collum);
		}
	};
	struct MyHash
	{
		std::size_t operator()(AxialCoordinates const& s) const noexcept
		{
			std::size_t h1 = std::hash<int>{}(s.row);
			std::size_t h2 = std::hash<int>{}(s.collum);
			return h1 ^ (h2 /*<< 1*/);
		}
	};

	struct Level;
	class GameObject;
	class TextureComponent;
	class Scene;
	class QBertMap
	{
	public:
		QBertMap(int windowWidth,int windowHeight, const Level& levelInfo);
		void LoadMap(Scene& sceneMan);
		GameObject* GetFirstBlock();
	private:
		void CreateGameBlocks();
		void CreateGameDisks(int row, int collum, int currentRow, int maxRow, float posx, float posy,float width, float height);


		
		const int m_WindowWidth;
		const int m_WindowHeight;
		std::vector<std::pair<std::string, std::string>> m_BlockFileNamesWithNickNames;
		std::string m_DiskAdressName;
		const std::string m_FilePath;
		int m_AmountOfCollums;
		std::vector<int> m_LeftFloatingDiscs;
		std::vector<int> m_RightFloatingDiscs;
		std::unordered_map<AxialCoordinates, std::shared_ptr<GameObject>, MyHash> m_UnMapBackgroundParts;
		bool m_PenaltyBlock;
		

	
		

	};
}
