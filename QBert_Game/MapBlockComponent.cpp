#include "MapBlockComponent.h"

#include <iostream>

#include "QBertMovementComponent.h"
#include "MapDiskComponent.h"
#include "GameObject.h"



dae::MapBlockComponent::MapBlockComponent(float x, float y, float width, float height, const  std::vector<std::string>& textureBlockNames, bool penalty)
	: MapPartComponent{ x,y,width,height,textureBlockNames, true,penalty }


{
}

dae::MapBlockComponent::~MapBlockComponent()//gives no memory leaks
{

}

void dae::MapBlockComponent::Update(float, GameObject&)
{
}

std::string dae::MapBlockComponent::GetTxt()
{
	return MapPartComponent::GetTxt();
}


void dae::MapBlockComponent::SubjectRender() const
{
}



dae::GameObject* dae::MapBlockComponent::HandleQbertMovement(GameObject* movQbert)
{
	return MapPartComponent::HandleQbertMovement(movQbert);
}



void dae::MapBlockComponent::NextBlockTexture()
{
	if (MapPartComponent::PlusNamesVecIndex())
	{
		MapPartComponent::SetPlatformStatus(PlatformStatus::gainedStatus);
		

	}
	else
	{
		MapPartComponent::SetPlatformStatus(PlatformStatus::none);
	}
}
void dae::MapBlockComponent::PenaltyChangeBlockTexture()
{
	if (MapPartComponent::MinusNamesVecIndex())
	{
		MapPartComponent::SetPlatformStatus(PlatformStatus::lostStatus);
	}
	else if (MapPartComponent::PlusNamesVecIndex())
	{
		MapPartComponent::SetPlatformStatus(PlatformStatus::gainedStatus);

	}
}

void dae::MapBlockComponent::ChangeMovementPosBlock(GameObject* movBlock)
{



	if (HasPenalty())
	{
		movBlock->GetComponent<MapBlockComponent>()->PenaltyChangeBlockTexture();

	}
	else
	{
		movBlock->GetComponent<MapBlockComponent>()->NextBlockTexture();
	}


}



