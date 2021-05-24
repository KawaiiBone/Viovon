#include "PLayerCoilyComponent.h"
#include "QBertComponentsHeaders.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "LivesComponent.h"
#include "Scene.h"

dae::PLayerCoilyComponent::PLayerCoilyComponent(GameObject* pBlockObject, int row, int collu, const std::vector<std::string>& textureNicknames, const std::string& soundPath) :
	PLayerComponent(pBlockObject, row, collu, soundPath),
	m_PlatStatus(PlatformStatus::none),
	m_IsInBallForm(true),
	m_VecTextureNames(textureNicknames),
	m_IndexTexturesNames(0),
	m_BallMoveCooldown{ 0.5,0.f, false }

{
}

void dae::PLayerCoilyComponent::Update(float deltaTime, GameObject& object)
{

	std::shared_ptr<dae::GameObject> tmpPointer = DidHitQBert();
	if (tmpPointer)
	{
		tmpPointer->GetComponent<LivesComponent>()->InfluenceLife(-1, tmpPointer);
		Reset(object);
		return;
	}
	
	m_BallMoveCooldown.cooldownCounter += deltaTime;
	
	if (m_BallMoveCooldown.cooldownCounter > m_BallMoveCooldown.cooldownDuration && m_IsInBallForm)
	{
		BallMovement(object);
	}


	if (!m_IsInBallForm)
	{
		PLayerComponent::Update(deltaTime, object);
	}



}

std::string dae::PLayerCoilyComponent::GetTxt() const
{
	return m_VecTextureNames[m_IndexTexturesNames];
}

dae::PlatformStatus dae::PLayerCoilyComponent::GetPlatformStatus()
{
	return m_PlatStatus;
}

void dae::PLayerCoilyComponent::SubjectRender() const
{
}

void dae::PLayerCoilyComponent::Reset(GameObject& object)
{
	m_IndexTexturesNames = 0;
	m_IsInBallForm = true;
	PLayerComponent::Reset(object);
}



void dae::PLayerCoilyComponent::BallMovement(GameObject& object)
{


	m_BallMoveCooldown.cooldownCounter = 0.f;

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
		m_IndexTexturesNames = 1;

		m_IsInBallForm = false;
	}
}

std::shared_ptr<dae::GameObject> dae::PLayerCoilyComponent::DidHitQBert() const
{


		if (SceneManager::GetInstance().GetPlayers()[0]->GetComponent<PLayerComponent>()->GetCoordinates() == GetCoordinates())
		{
			return SceneManager::GetInstance().GetPlayers()[0];
		}

	return nullptr;
}
