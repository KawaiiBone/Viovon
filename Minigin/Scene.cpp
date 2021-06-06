#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "../QBert_Game/MapPartComponent.h"
#include "../QBert_Game/PLayerComponent.h"
#include "../QBert_Game/MapDiskComponent.h"
#include <algorithm>

#include "ScoreComponent.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const TypeOfScene typescene) : m_TypeScene(typescene) {}


void Scene::AddMap(const std::unordered_map<AxialCoordinates, std::shared_ptr<GameObject>, MyHash>& Unmap)
{
	m_UnMap = Unmap;
}

bool Scene::HasFinishedLevel()
{

	return std::all_of(m_UnMap.begin(), m_UnMap.end(), [](auto& a) {return a.second->GetComponent<MapPartComponent>()->PlatformDone(); });


}

void Scene::FinishLevel(std::vector<std::shared_ptr<GameObject>>& players)
{
	const int score{ 25 };
	const int totalDisks{ int(AmountOfRemainingDisks()) };

	if (totalDisks > 0)
	{

		for (std::shared_ptr<GameObject>& element : players)
		{
			auto tmpComp = element->GetComponent<ScoreComponent>();
			if (tmpComp)
			{
				tmpComp->InfluenceScore(score * totalDisks, element);
			}
		}
	}


}

void Scene::PlayersToStartingPos(std::vector<std::shared_ptr<GameObject>>& players)
{
	for (auto& element : m_PlayerStartingCoordinates)
	{
		if (element.first == SceneManager::GetInstance().GetGameMode())
		{
			for (size_t i = 0; i < players.size(); ++i)
			{
				auto tmpComp{ players[i]->GetComponent<PLayerComponent>() };
				//auto tmpComp{ players[i]->GetComponent<QBertMovementComponent>() };
				tmpComp->SetCoordinates(element.second[i]);
				tmpComp->SetBlockObject(m_UnMap[element.second[i]].get());
				players[i]->SetPosition(m_UnMap[element.second[i]]->GetComponent<MapPartComponent>()->GetPlatformPos().x, m_UnMap[element.second[i]]->GetComponent<MapPartComponent>()->GetPlatformPos().y);
				Add(players[i]);
			}
			return;
		}
	}



}

void Scene::SetPlayerStartingCoordinates(const std::vector<std::pair<GameMode, std::vector<AxialCoordinates>>>& startCoordinates)
{
	m_PlayerStartingCoordinates = startCoordinates;
}

void Scene::ResetScene()
{
	for (auto& object : m_Objects)
	{
		object->ResetObject();
	}
	for (auto& element : m_UnMap)
	{
		element.second->ResetObject();
	}
	for (auto& object : m_BackgroundObjects)
	{
		object->ResetObject();
	}

}

size_t Scene::AmountOfRemainingDisks()
{
	return std::count_if(m_UnMap.begin(), m_UnMap.end(), [](auto& a) {return a.second->GetComponent<MapDiskComponent>() != nullptr; });
}


Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>&object/*, bool IsPlayer*/)
{
	m_Objects.push_back(object);

}

void Scene::AddBackground(const std::shared_ptr<GameObject>&object)
{
	m_BackgroundObjects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	for (auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
	for (auto& element : m_UnMap)
	{
		element.second->Update(deltaTime);
	}
	for (auto& object : m_BackgroundObjects)
	{
		object->Update(deltaTime);
	}


	DestroyDeadObjects();
}

void Scene::Render() const
{
	for (auto& element : m_BackgroundObjects)
	{
		element->Render();
	}
	for (auto& element : m_UnMap)
	{
		element.second->Render();
	}
	for (const auto& object : m_Objects)
	{
		object->Render();
	}




}

TypeOfScene Scene::GetSceneName() const
{
	return m_TypeScene;
}

std::pair<AxialCoordinates, GameObject*>Scene::GetMapPart(int row, int collum)
{
	// info from: https://www.cplusplus.com/reference/unordered_map/unordered_map/find/
	std::unordered_map<AxialCoordinates, std::shared_ptr<GameObject>, MyHash>::const_iterator got = m_UnMap.find(AxialCoordinates{ row, collum });
	if (got == m_UnMap.end())
	{
		return { AxialCoordinates{0,0},nullptr };
	}
	return { AxialCoordinates{row,collum},got->second.get() };
}


void Scene::DestroyDeadObjects()
{
	// source: https://stackoverflow.com/questions/39019806/using-erase-remove-if-idiom


	m_Objects.erase(std::remove_if(m_Objects.begin(),
		m_Objects.end(),
		[&](const std::shared_ptr<GameObject> stopPoint)-> bool
		{ return stopPoint->IsDead(); }),
		m_Objects.end());

	// source  https://en.cppreference.com/w/cpp/container/unordered_map/erase
	for (auto it = m_UnMap.begin(); it != m_UnMap.end(); ) {
		if (it->second->IsDead())
			it = m_UnMap.erase(it);
		else
			++it;
	}

}
