﻿#include "UggOrWrongwayAiComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "MapPartComponent.h"
#include "QBertMovementComponent.h"



dae::UggOrWrongwayAiComponent::UggOrWrongwayAiComponent(int Row, const std::vector<std::string>& vecTextureNames) :
	AIBaseComponent(Row, 6, 0.85f, vecTextureNames)

{
	if (Row > 0)
	{
		m_StartedLeft = false;
	}
	else
	{
		m_StartedLeft = true;
	}

}

dae::UggOrWrongwayAiComponent::~UggOrWrongwayAiComponent()
{
	/*delete m_pBlockObject;
	m_pBlockObject = nullptr;*/
}

void dae::UggOrWrongwayAiComponent::Update(float delta, GameObject& object)
{
	if (DidHitQBert())
	{
		object.Die();
	}


	if (!IsInCooldown(delta))
	{
		Movement(object);
	}




}

std::string dae::UggOrWrongwayAiComponent::GetTxt()
{
	return AIBaseComponent::GetTxt();
}


void dae::UggOrWrongwayAiComponent::SubjectRender() const
{
}


void dae::UggOrWrongwayAiComponent::Movement(GameObject& object)
{
	ResetCooldownCounter();


	int randomCollum{ rand() % (1 + 1) - 1 };
	int rowPart{ 0 };
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	std::pair<AxialCoordinates, GameObject*>mapPartObject{};
	if (m_StartedLeft)
	{
		
		 mapPartObject = scene->GetMapPart(GetCoordinates().row + 1, GetCoordinates().collum + randomCollum);
	}
	else
	{
		if (randomCollum == 0)
		{
			rowPart = 1;
		}
			mapPartObject = scene->GetMapPart(GetCoordinates().row - rowPart, GetCoordinates().collum + randomCollum);
	}
	std::cout << mapPartObject.first.row << "   " << mapPartObject.first.collum << "\n";


	
	if (mapPartObject.second)
	{
		mapPartObject.second->GetComponent<MapPartComponent>()->HandleAiMovement();
		auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();
		SetCoordinates(mapPartObject.first);
		if (m_StartedLeft)
		{
			object.SetPosition(mapPartObjectComp->GetUggPlatformPos().x, mapPartObjectComp->GetUggPlatformPos().y);
		}
		else
		{
			object.SetPosition(mapPartObjectComp->GetWrongWayPlatformPos().x, mapPartObjectComp->GetWrongWayPlatformPos().y);
		}
	}
	else
	{
		object.Die();
	}



}