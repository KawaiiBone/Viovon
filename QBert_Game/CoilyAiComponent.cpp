#include "CoilyAiComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "MapPartComponent.h"
#include "QBertMovementComponent.h"


dae::CoilyAiComponent::CoilyAiComponent(int Row, const std::vector<std::string>& vecTextureNames, float spawnTime):
	AIBaseComponent(Row,1,0.85f, vecTextureNames, spawnTime),
	m_IsInBallForm{ true }
{




}

dae::CoilyAiComponent::~CoilyAiComponent()
{
	/*delete m_pBlockObject;
	m_pBlockObject = nullptr;*/
}

void dae::CoilyAiComponent::Update(float delta, GameObject& object)
{
	if (!IsInSpawnCooldown(delta, object))
	{
		if (DidHitQBert())
		{
			return; //add something here!!!!
		}


		if (IsInMovementCooldown(delta))
		{
			return;
		}
		else if (m_IsInBallForm)
		{

			BallMovement(object);
		}
		else
		{
			CoilyMovement(object);
		}

	}
}

std::string dae::CoilyAiComponent::GetTxt()
{
	return AIBaseComponent::GetTxt();
}


void dae::CoilyAiComponent::SubjectRender() const
{
}


void dae::CoilyAiComponent::BallMovement(GameObject& object)
{
	ResetCooldownCounter();


	//srand(unsigned int(time(nullptr)));

	int randomRow{ rand() % (1 + 1) - 1 };
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	auto mapPartObject = scene->GetMapPart(GetCoordinates().row + randomRow, GetCoordinates().collum + 1);

	if (mapPartObject.second)
	{
		auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();
		SetCoordinates(mapPartObject.first);
		object.SetPosition(mapPartObjectComp->GetPlatformPos().x, mapPartObjectComp->GetPlatformPos().y);
	}
	else
	{
		NextTexture();
	
		m_IsInBallForm = false;
	}



}

void dae::CoilyAiComponent::CoilyMovement(GameObject& object)
{


	ResetCooldownCounter();

	int tmpRow{ GetCoordinates().row };
	int tmpCollum{ GetCoordinates().collum };
	if (object.GetPosition().GetPosition().y >= GetPQBertObject()->GetPosition().GetPosition().y)
	{
		tmpCollum--;
	}
	else
	{
		tmpCollum++;
	}
	if (object.GetPosition().GetPosition().x >= GetPQBertObject()->GetPosition().GetPosition().x)
	{
		if (tmpCollum > GetCoordinates().collum)
		{
			tmpRow--;
		}

	}
	else
	{
		if (tmpCollum < GetCoordinates().collum)
		{
			tmpRow++;
		}

	}


	auto scene = SceneManager::GetInstance().GetCurrentScene();
	auto mapPartObject = scene->GetMapPart(tmpRow, tmpCollum);

	if (mapPartObject.second)
	{
		auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();
		SetCoordinates(mapPartObject.first);
		object.SetPosition(mapPartObjectComp->GetPlatformPos().x, mapPartObjectComp->GetPlatformPos().y);



	}
}



//dae::CoilyAiComponent::CoilyAiComponent(int Row, const std::vector<std::string>& vecTextureNames)
//	: m_Row(Row),
//	m_Collum(1),
//	m_MovementCooldown{ 0.85f,0.f, true },
//	m_VecTextureNames(vecTextureNames),
//	m_IndexTexturesNames(0),
//	m_IsInBallForm{ true }
//{
//
//	m_QbertObject = SceneManager::GetInstance().GetPlayers()[0].get();
//	auto scene = SceneManager::GetInstance().GetCurrentScene();
//	m_pBlockObject = scene->GetMapPart(m_Row, m_Collum).second;
//
//
//}
//
//dae::CoilyAiComponent::~CoilyAiComponent()
//{
//	/*delete m_pBlockObject;
//	m_pBlockObject = nullptr;*/
//}
//
//void dae::CoilyAiComponent::Update(float delta, GameObject& object)
//{
//	if (DidHitQBert())
//	{
//		return; //add something here!!!!
//	}
//
//
//
//
//	
//	if (m_MovementCooldown.cooldownCounter < m_MovementCooldown.cooldownDuration)
//	{
//		m_MovementCooldown.cooldownCounter += delta;
//
//	}
//	else if(m_IsInBallForm)
//	{
//		
//		BallMovement(object);
//	}
//	else 
//	{
//		CoilyMovement(object);
//	}
//
//
//}
//
//void dae::CoilyAiComponent::SetBlockObject(GameObject* pBlockObject)
//{
//
//	m_pBlockObject = pBlockObject;
//}
//
//bool dae::CoilyAiComponent::DidHitQBert()
//{
//	if (m_QbertObject->GetComponent<QBertMovementComponent>()->GetCoordinates() == AxialCoordinates{m_Row,m_Collum})
//	{
//		return true;
//	}
//	return false;
//}
//
//
//std::string dae::CoilyAiComponent::GetTxt()
//{
//	return m_VecTextureNames[m_IndexTexturesNames];
//}
//
//void dae::CoilyAiComponent::SubjectRender() const
//{
//}
//
//
//
//
//void dae::CoilyAiComponent::SetCoordinates(AxialCoordinates coordinates)
//{
//	m_Row = coordinates.row;
//	m_Collum = coordinates.collum;
//}
//
//
//
//
//
//
//bool dae::CoilyAiComponent::CanHandleMovement(GameObject* movQbert)
//{
//	//auto tmpP = m_pBlockObject->GetComponent<MapBlockComponent>()->HandleQbertMovement(movQbert);
//	auto tmpP = m_pBlockObject->GetComponent<MapPartComponent>()->HandleQbertMovement(movQbert);
//	if (tmpP)
//	{
//		m_MovementCooldown.cooldownOver = false;
//		m_MovementCooldown.cooldownCounter = 0.f;
//		SetBlockObject(tmpP);
//		return true;
//	}
//	return false;
//}
//
//void dae::CoilyAiComponent::BallMovement(GameObject& object)
//{
//	m_MovementCooldown.cooldownCounter = 0.f;
//
//
//	//srand(unsigned int(time(nullptr)));
//
//	int randomRow{ rand() % (1 + 1) - 1 };
//	auto scene = SceneManager::GetInstance().GetCurrentScene();
//	auto mapPartObject = scene->GetMapPart(m_Row + randomRow, m_Collum + 1);
//
//	if (mapPartObject.second)
//	{
//		auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();
//		SetCoordinates(mapPartObject.first);
//		object.SetPosition(mapPartObjectComp->GetPlatformPos().x, mapPartObjectComp->GetPlatformPos().y);
//	}
//	else
//	{
//		m_IndexTexturesNames = 1;
//		m_IsInBallForm = false;
//	}
//
//
//
//}
//
//void dae::CoilyAiComponent::CoilyMovement(GameObject& object)
//{
//
//
//
//
//	
//	m_MovementCooldown.cooldownCounter = 0.f;
//
//	int tmpRow{ m_Row };
//	int tmpCollum{ m_Collum };
//	if (object.GetPosition().GetPosition().y >= m_QbertObject->GetPosition().GetPosition().y)
//	{
//		tmpCollum--;
//	}
//	else
//	{
//		tmpCollum++;
//	}
//	if(object.GetPosition().GetPosition().x >= m_QbertObject->GetPosition().GetPosition().x)
//	{
//		if (tmpCollum > m_Collum)
//		{
//			tmpRow--;
//		}
//	
//	}
//	else
//	{
//		if (tmpCollum < m_Collum)
//		{
//			tmpRow++;
//		}
//		
//	}
//	
//	
//	auto scene = SceneManager::GetInstance().GetCurrentScene();
//	auto mapPartObject = scene->GetMapPart(tmpRow, tmpCollum);
//
//	if (mapPartObject.second)
//	{
//		auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();
//		SetCoordinates(mapPartObject.first);
//		object.SetPosition(mapPartObjectComp->GetPlatformPos().x, mapPartObjectComp->GetPlatformPos().y);
//
//
//		
//	}
//}
