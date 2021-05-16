#include "MapDiskComponent.h"
#include "QBertMovementComponent.h"
#include "MapBlockComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"



dae::MapDiskComponent::MapDiskComponent(float, float, float width, float height) :
	MapPartComponent(0.f, 0.f, width, height,{}, false)
	


{

}

dae::MapDiskComponent::~MapDiskComponent()//gives no memory leaks
{

}

void dae::MapDiskComponent::Update(float, GameObject&)
{
}

std::string dae::MapDiskComponent::GetTxt()
{
	return "0";
}


void dae::MapDiskComponent::SubjectRender() const
{
}



dae::GameObject* dae::MapDiskComponent::HandleQbertMovement(GameObject* movQbert, bool penaltyBlock)
{

	auto scene = SceneManager::GetInstance().GetPointerScene(TypeOfScene::demo);
	auto object = scene->GetMapPart(6, 0).second;
	object->GetComponent<MapBlockComponent>()->ChangeMovementPosBlock(object, penaltyBlock);
	movQbert->Die();
	return object;


}





void dae::MapDiskComponent::ChangeMovementPosBlock(GameObject*, bool )
{


}





