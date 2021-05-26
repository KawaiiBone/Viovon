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
		Level(int mapSize,const std::vector<int>& leftFloatDisc,const std::vector<int>& rightFloatDisc, const std::vector<std::string>& blockTextureAdres, 
			const std::vector<std::string>& blockTextureNick,const std::string & discAdress, bool coilyspawn,float cSpawnTime ,
			const std::vector <float>& uggSpawntimes, const std::vector <float>& SlickSpawntimes, bool penalty):
			mapSizeColumns(mapSize),
			leftFloatingDiscs(leftFloatDisc),
			rightFloatingDiscs(rightFloatDisc),
			blockTextureAdressNames(blockTextureAdres),
			blockTextureNickNames(blockTextureNick),
			diskAdress(discAdress),
			coilySpawn(coilyspawn),
			coilySpawnTime(cSpawnTime),
			uggAbdWrongwaySpawnTimes(uggSpawntimes),
			slickAndSamSpawnTimes(SlickSpawntimes),
			penaltyBlocks(penalty)
		{
		}
		Level():
			mapSizeColumns(0),
			leftFloatingDiscs({}),
			rightFloatingDiscs({}),
			blockTextureAdressNames({}),
			blockTextureNickNames({}),
			diskAdress(""),
			coilySpawn(false),
			coilySpawnTime(0),
			uggAbdWrongwaySpawnTimes({}),
			slickAndSamSpawnTimes({}),
			penaltyBlocks(false)
		{}
	};
	
	class QBertLevel
	{
	public:

		QBertLevel(TypeOfScene typeScene, int windowWidth, int windowHeight, const  Level& level);

		void CreateLevel();
	private:
		void CreateBackground(Scene& scene);
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
