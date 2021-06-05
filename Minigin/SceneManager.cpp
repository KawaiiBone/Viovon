#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>

#include "GameObject.h"


void dae::SceneManager::Update(float deltaTime)
{


	m_Scenes[m_ScenesVecIndex].first->Update(deltaTime);

}

void dae::SceneManager::Render() const
{
	m_Scenes[m_ScenesVecIndex].first->Render();

}



std::vector<std::shared_ptr<dae::GameObject>> dae::SceneManager::GetPlayers()
{
	return m_pPlayers;
}



void dae::SceneManager::AddPlayer(std::shared_ptr<GameObject>& object)
{
	m_pPlayers.push_back(object);
}

void dae::SceneManager::ChangeScene(const TypeOfScene typeScene)
{

	int counter{ 0 };
	const int score{ 50 };
	for (std::pair<std::shared_ptr<Scene>, TypeOfScene>& element : m_Scenes)
	{
		if (element.second == typeScene)
		{
			if (m_ScenesVecIndex != counter)
			{
				m_ScenesVecIndex = counter;
				m_Scenes[m_ScenesVecIndex-1].first->FinishLevel(m_pPlayers);
			}
			m_Scenes[m_ScenesVecIndex].first->PlayersToStartingPos(m_pPlayers);
			
			return;
		}
		counter++;
	}
}

void dae::SceneManager::SetGameMode(GameMode gameMode)
{
	m_GameMode = gameMode;
}

dae::GameMode dae::SceneManager::GetGameMode() const
{
	return m_GameMode;
}

void dae::SceneManager::ResetScenes()
{
	for (std::pair<std::shared_ptr<Scene>, TypeOfScene>& element : m_Scenes)
	{
		element.first->ResetScene();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const TypeOfScene typeScene)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(typeScene));
	m_Scenes.push_back({ scene, typeScene });
	return *scene;
}

std::shared_ptr<dae::Scene>	 dae::SceneManager::GetPointerScene(const TypeOfScene sceneName)
{

	auto tmpScene = std::find_if(m_Scenes.begin(), m_Scenes.end(), [sceneName](auto& a) {return a.second == sceneName; });

	if (tmpScene == m_Scenes.end())
	{
		return nullptr;
	}
	return tmpScene->first;

}

std::shared_ptr<dae::Scene> dae::SceneManager::GetCurrentScene()
{
	return m_Scenes[m_ScenesVecIndex].first;
}
