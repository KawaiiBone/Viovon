#include "SlickOrSlamAiComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "MapPartComponent.h"
#include "QBertMovementComponent.h"



dae::SlickOrSlamAiComponent::SlickOrSlamAiComponent(int Row, const std::vector<std::string>& vecTextureNames, float spawnTime) :
	AIBaseComponent(Row, 1, 0.85f, vecTextureNames, spawnTime)

{




}

dae::SlickOrSlamAiComponent::~SlickOrSlamAiComponent()
{
	/*delete m_pBlockObject;
	m_pBlockObject = nullptr;*/
}

void dae::SlickOrSlamAiComponent::Update(float delta, GameObject& object)
{
	if (!IsInSpawnCooldown(delta, object))
	{
		if (DidHitQBert())
		{
			object.Die();
		}


		if (!IsInMovementCooldown(delta))
		{
			Movement(object);
		}
	}



}

std::string dae::SlickOrSlamAiComponent::GetTxt()
{
	return AIBaseComponent::GetTxt();
}


void dae::SlickOrSlamAiComponent::SubjectRender() const
{
}


void dae::SlickOrSlamAiComponent::Movement(GameObject& object)
{
	ResetCooldownCounter();


	//srand(unsigned int(time(nullptr)));

	int randomRow{ rand() % (1 + 1) - 1 };
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	auto mapPartObject = scene->GetMapPart(GetCoordinates().row + randomRow, GetCoordinates().collum + 1);

	if (mapPartObject.second)
	{
		mapPartObject.second->GetComponent<MapPartComponent>()->HandleAiMovement();
		auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();
		SetCoordinates(mapPartObject.first);
		object.SetPosition(mapPartObjectComp->GetPlatformPos().x, mapPartObjectComp->GetPlatformPos().y);
	}
	else
	{
		object.Die();
	}



}
