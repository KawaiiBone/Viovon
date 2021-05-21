#pragma once
#include "InterfaceWindow.h"
#include "SceneManager.h"
#include "unordered_map"
#include "../QBert_Game/QBertMap.h"

namespace dae
{
	class GameObject;


	enum class InterFaceNames;


	
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const TypeOfScene typescene);
	public:
		void Add(const std::shared_ptr<GameObject>& object/*, bool IsPlayer*/);
		void AddBackground(const std::shared_ptr<GameObject>& object/*, bool IsPlayer*/);

		void Update(float deltaTime);
		void Render() const;
		TypeOfScene GetSceneName()const;
		std::pair<AxialCoordinates,GameObject*> GetMapPart(int row, int collum);
		void AddMap(const std::unordered_map<AxialCoordinates,std::shared_ptr<GameObject>, MyHash>& Unmap );

		bool HasFinishedLevel();
		void FinishLevel(std::vector<std::shared_ptr<GameObject>>& players);
		void PlayersToStartingPos(std::vector < std::shared_ptr<GameObject>>& players);

		void SetPlayerStartingCoordinates(const std::vector<std::pair<GameMode, std::vector<AxialCoordinates>>>& startCoordinates);
		void ResetScene();
		size_t AmountOfRemainingDisks();
		
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const TypeOfScene typescene);
		void DestroyDeadObjects();

		const TypeOfScene  m_TypeScene;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::vector < std::shared_ptr<GameObject>> m_BackgroundObjects{};
		std::unordered_map<AxialCoordinates, std::shared_ptr<GameObject>, MyHash> m_UnMap;
		static unsigned int m_IdCounter;
		std::vector<std::pair<GameMode, std::vector<AxialCoordinates>>> m_PlayerStartingCoordinates;

	};

}
