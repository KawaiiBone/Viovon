#include "MapDiskComponent.h"
#include "QBertMovementComponent.h"
#include "MapBlockComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"



dae::MapDiskComponent::MapDiskComponent(float, float) :
	MapPartComponent(0.f, 0.f, {}, false)
	


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



dae::GameObject* dae::MapDiskComponent::HandleQbertMovement(GameObject* /*movQbert*/)
{

	//auto scene = SceneManager::GetInstance().GetPointerScene(TypeOfScene::demo);
	// return scene->GetMapPart( 6,0 ).second;
	return nullptr;

}





void dae::MapDiskComponent::ChangeMovementPosBlock(GameObject*)
{


}


//dae::MapDiskComponent::MapDiskComponent(float, float , const std::vector<MovementPosBlock>& movPosBlocksVec, const std::vector<std::string>& textureBlockNames)
//	: MapPartComponent{ movPosBlocksVec.front().pBlockObject->GetComponent<MapPartComponent>()->GetPlatformPos().x,movPosBlocksVec.front().pBlockObject->GetComponent<MapPartComponent>()->GetPlatformPos().y,movPosBlocksVec,textureBlockNames, false }
//	, m_HighestBlock(movPosBlocksVec.front().pBlockObject)
//
//
//{
//	
//}
//
//dae::MapDiskComponent::~MapDiskComponent()//gives no memory leaks
//{
//
//}
//
//void dae::MapDiskComponent::Update(float, GameObject&)
//{
//}
//
//std::string dae::MapDiskComponent::GetTxt()
//{
//	return "0";
//}
//
//
//void dae::MapDiskComponent::SubjectRender() const
//{
//}
//
//
//
//dae::GameObject* dae::MapDiskComponent::HandleQbertMovement(MovementQbert /*movQbert*/)
//{
//
//
//	//m_HighestBlock->GetComponent<MapBlockComponent>()->ChangeMovementPosBlock(m_HighestBlock);
//	return m_HighestBlock;
//	//return MapPartComponent::HandleQbertMovement(movQbert);
//}
//
//
//
//
//
//void dae::MapDiskComponent::ChangeMovementPosBlock(GameObject* )
//{
//
//	
//}


