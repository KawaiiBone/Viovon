#include "CoilyAiComponent.h"
#include "GameObject.h"
#include "LivesComponent.h"
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
		std::shared_ptr<dae::GameObject> tmpPointer = DidHitQBert();
		if (tmpPointer)
		{
			tmpPointer->GetComponent<LivesComponent>()->InfluenceLife(-1, tmpPointer);
			Respawn(object);
			return;
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

std::string dae::CoilyAiComponent::GetTxt() const
{
	return AIBaseComponent::GetTxt();
}


void dae::CoilyAiComponent::SubjectRender() const
{
}

void dae::CoilyAiComponent::Reset(GameObject& /*object*/)
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




