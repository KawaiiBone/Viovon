#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const TypeOfScene typescene) : m_TypeScene(typescene) {}




Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object/*, bool IsPlayer*/)
{
	m_Objects.push_back(object);
	/*if (IsPlayer)
	{
		m_pPlayer = object;
	}*/
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}

	DestroyDeadObjects();
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

TypeOfScene Scene::GetSceneName() const
{
	return m_TypeScene;
}


void Scene::DestroyDeadObjects()
{
	// source: https://stackoverflow.com/questions/39019806/using-erase-remove-if-idiom

	
	m_Objects.erase(std::remove_if(m_Objects.begin(),
		m_Objects.end(),
		[&](const std::shared_ptr<GameObject> stopPoint)-> bool
		{ return stopPoint->IsDead(); }),
		m_Objects.end());


}
