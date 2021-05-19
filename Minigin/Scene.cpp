#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const TypeOfScene typescene) : m_TypeScene(typescene){}


void Scene::AddMap(const std::unordered_map<AxialCoordinates, std::shared_ptr<GameObject>, MyHash>& Unmap)
{
	m_UnMap = Unmap;
}



Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object/*, bool IsPlayer*/)
{
	m_Objects.push_back(object);
	/*if (IsPlayer)
	{
		m_pPlayer = object;
	}*/
}

void Scene::AddBackground(const std::shared_ptr<GameObject>& object)
{
	m_BackgroundObjects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
	for (auto element : m_UnMap)
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
	for (auto element : m_BackgroundObjects)
	{
		element->Render();
	}
	for (auto element : m_UnMap)
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
	std::unordered_map<AxialCoordinates, std::shared_ptr<GameObject>, MyHash>::const_iterator got = m_UnMap.find(AxialCoordinates{row, collum});
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
