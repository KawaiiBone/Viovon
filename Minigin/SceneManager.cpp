#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}



std::vector<std::shared_ptr<dae::GameObject>> dae::SceneManager::GetPlayers()
{
	return m_pPlayers;
}



void dae::SceneManager::AddPlayer(std::shared_ptr<GameObject>& object)
{
	m_pPlayers.push_back(object);
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

std::shared_ptr<dae::Scene>	 dae::SceneManager::GetPointerScene(const std::string& name)
{
	for (auto scene : m_Scenes)
	{
		if (scene->GetSceneName() == name)
		{
			return scene;
		}
	}
	return nullptr;
}
