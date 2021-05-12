#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{


	m_Scenes[m_ScenesVecIndex].first->Update(deltaTime);
	//for(auto& scene : m_Scenes)
	//{
	//	scene->Update(deltaTime);
	//}
}

void dae::SceneManager::Render() const
{
	m_Scenes[m_ScenesVecIndex].first->Render();
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->Render();
	//}
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
	for (std::pair<std::shared_ptr<Scene>, TypeOfScene> element : m_Scenes)
	{
		if (element.second == typeScene)
		{
			m_ScenesVecIndex = counter;
			return;
		}
		counter++;
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
	for (std::pair<std::shared_ptr<Scene>, TypeOfScene> scene : m_Scenes)
	{
		if (scene.second == sceneName)
		{
			return scene.first;
		}
	}
	return nullptr;
}
