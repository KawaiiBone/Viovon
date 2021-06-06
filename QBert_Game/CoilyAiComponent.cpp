#include "CoilyAiComponent.h"
#include "GameObject.h"
#include "LivesComponent.h"
#include "Scene.h"
#include "MapPartComponent.h"
#include "PLayerComponent.h"
#include "ScoreComponent.h"


dae::CoilyAiComponent::CoilyAiComponent(int Row, const std::vector<std::string>& vecTextureNames, float spawnTime, const std::string& soundPath):
	AIBaseComponent(Row,1,0.85f, vecTextureNames, spawnTime, soundPath),
	m_IsInBallForm{ true },
	m_Score(500)
{




}

dae::CoilyAiComponent::~CoilyAiComponent()
{
	/*delete m_pBlockObject;
	m_pBlockObject = nullptr;*/
}

void dae::CoilyAiComponent::Update(float delta, GameObject& object)
{
	if (SceneManager::GetInstance().GetGameMode() == GameMode::versus)
	{
		object.Die();
	}
	else if (!IsInSpawnCooldown(delta, object))
	{
		std::shared_ptr<dae::GameObject> tmpPointer = DidHitQBert();
		if (tmpPointer)
		{
			tmpPointer->GetComponent<LivesComponent>()->InfluenceLife(-1, tmpPointer);
			Respawn(object);
			m_IsInBallForm = true;
			return;
		}
	
		


		if (IsInMovementCooldown(delta))
		{
			return;
		}
		if (m_IsInBallForm)
		{

			BallMovement(object);
		}
		else
		{
			CoilyMovement(object);
		}

	}
}

std::string dae::CoilyAiComponent::GetTxt() const
{
	return AIBaseComponent::GetTxt();
}


void dae::CoilyAiComponent::SubjectRender() const
{
}

void dae::CoilyAiComponent::Reset(GameObject& /*object*/)
{
	m_IsInBallForm = true;
}

bool dae::CoilyAiComponent::HasQbertJumpedOnDisk() const
{
	const auto& playComp = GetPQBertObject()->GetComponent<PLayerComponent>();
	if (playComp->GetOldCoordinates().row == playComp->GetCoordinates().row)
	{
		if (playComp->GetOldCoordinates().collum +1 == playComp->GetCoordinates().collum || playComp->GetOldCoordinates().collum - 1 == playComp->GetCoordinates().collum)
		{
			return false;
		}
		return true;
		
	}
	if(playComp->GetOldCoordinates().row-1 == playComp->GetCoordinates().row && playComp->GetOldCoordinates().collum + 1 == playComp->GetCoordinates().collum)
	{
		return false;
	}
	if (playComp->GetOldCoordinates().row + 1 == playComp->GetCoordinates().row && playComp->GetOldCoordinates().collum - 1 == playComp->GetCoordinates().collum)
	{
		return false;
	}
	return true;
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

	const auto& playComp = GetPQBertObject()->GetComponent<PLayerComponent>();

	float qBertPosX{ 0.f };
	float qBertPosY{ 0.f };
	int tmpRow{ GetCoordinates().row };
	int tmpCollum{ GetCoordinates().collum };
	
	if (playComp->GetOldCoordinates()!= GetCoordinates())
	{
		auto tmpBlock = SceneManager::GetInstance().GetCurrentScene()->GetMapPart( playComp->GetOldCoordinates().row, playComp->GetOldCoordinates().collum).second;
		qBertPosX = tmpBlock->GetPosition().GetPosition().x;
		qBertPosY = tmpBlock->GetPosition().GetPosition().y;
	}
	else
	{
		if (!HasQbertJumpedOnDisk())
		{
			qBertPosX = GetPQBertObject()->GetPosition().GetPosition().x;
			qBertPosY = GetPQBertObject()->GetPosition().GetPosition().y;
		}
		else
		{
			GetPQBertObject()->GetComponent<ScoreComponent>()->InfluenceScore(m_Score,SceneManager::GetInstance().GetPlayers()[0] );
			PlaySound();
			Respawn(object);
			m_IsInBallForm = true;
			return;

		}
	
	}


	if (object.GetPosition().GetPosition().y >= qBertPosY)
	{
		tmpCollum--;
	}
	else
	{
		tmpCollum++;
	}
	if (object.GetPosition().GetPosition().x >= qBertPosX)
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
		PlaySound();


	}
}




