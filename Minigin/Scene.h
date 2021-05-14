#pragma once
#include "SceneManager.h"
#include "unordered_map"
#include "../QBert_Game/QBertMap.h"

namespace dae
{
	class GameObject;

	//struct AxialCoordinates
	//{
	//	int row;
	//	int collum;

	//	bool operator==(const AxialCoordinates& other) const
	//	{
	//		return (row == other.row
	//			&& collum == other.collum);
	//	}
	//};
	//struct MyHash
	//{
	//	std::size_t operator()(AxialCoordinates const& s) const noexcept
	//	{
	//		std::size_t h1 = std::hash<int>{}(s.row);
	//		std::size_t h2 = std::hash<int>{}(s.collum);
	//		return h1 ^ (h2 /*<< 1*/);
	//	}
	//};




	
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const TypeOfScene typescene);
	public:
		void Add(const std::shared_ptr<GameObject>& object/*, bool IsPlayer*/);
		void AddBackground(const std::shared_ptr<GameObject>& object/*, bool IsPlayer*/);

		void Update(float deltaTime);
		void Render() const;
		TypeOfScene GetSceneName()const;
		//get map
		std::pair<AxialCoordinates,GameObject*> GetMapPart(int row, int collum);
		void AddMap(const std::unordered_map<AxialCoordinates,std::shared_ptr<GameObject>, MyHash>& Unmap );
		
		
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
	};

}
