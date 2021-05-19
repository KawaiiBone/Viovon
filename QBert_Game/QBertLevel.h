#pragma once
#include "QBert.h"
#include "QBertMap.h"
#include "Scene.h"
namespace dae
{
	struct Level
	{
		int mapSizeColumns;
		std::vector<int>	leftFloatingDiscs;
		std::vector<int>	rightFloatingDiscs;
		std::vector<std::string> blockTextureAdressNames;
		std::vector<std::string> blockTextureNickNames;
		std::string diskAdress;
		bool coilySpawn;
		float coilySpawnTime;
		std::vector <float> uggAbdWrongwaySpawnTimes;
		std::vector <float> slickAndSamSpawnTimes;
		bool penaltyBlocks;
	};
	
	class QBertLevel
	{
	public:

		QBertLevel(TypeOfScene typeScene, int windowWidth, int windowHeight, const  Level& level);

		void CreateLevel();
	private:
		void CreateStartingCoordinatesPlayers();
		void AddPlayers(Scene& scene);
		void LoadCoily(const bool coilySpawn, Scene& scene)const;
		void LoadUggAbdWrongway(Scene& scene)const;
		void LoadSlickAndSam(Scene& scene)const;
		dae::QBertMap m_Map;
		const TypeOfScene m_TypeScene;
		const Level m_LevelInfo;
		std::vector<std::pair<GameMode, std::vector<AxialCoordinates>>>m_PlayerStartingCoordinates;
	};
}
