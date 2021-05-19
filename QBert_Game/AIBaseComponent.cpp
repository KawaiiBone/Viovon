#include "AIBaseComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "MapPartComponent.h"
#include "QBertMovementComponent.h"


dae::AIBaseComponent::AIBaseComponent(int row, int collum, float cooldownDuration,const std::vector<std::string>& vecTextureNames, float spawnTime)
	: m_Row(row),
	m_Collum(collum),
	m_MovementCooldown{ cooldownDuration,0.f, true },
	m_VecTextureNames(vecTextureNames),
	m_IndexTexturesNames(0),
	m_SpawnCooldown{ spawnTime,0.f,false }

{

	m_QbertObject = SceneManager::GetInstance().GetPlayers()[0].get();
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	m_pBlockObject = scene->GetMapPart(m_Row, m_Collum).second;


}

dae::AIBaseComponent::~AIBaseComponent()
{
	/*delete m_pBlockObject;
	m_pBlockObject = nullptr;*/
}



void dae::AIBaseComponent::SetBlockObject(GameObject* pBlockObject)
{

	m_pBlockObject = pBlockObject;
}

std::shared_ptr<dae::GameObject> dae::AIBaseComponent::DidHitQBert() const
{


	
	for (auto element : SceneManager::GetInstance().GetPlayers())
	{
		if (element->GetComponent<QBertMovementComponent>()->GetCoordinates() == AxialCoordinates{ m_Row,m_Collum })
		{
			return element;
		}
	
	}
	return nullptr;
	
}

void dae::AIBaseComponent::ResetCooldownCounter()
{
	m_MovementCooldown.cooldownCounter = 0.f;
}

bool dae::AIBaseComponent::IsInMovementCooldown(float deltaTime)
{
	if (m_MovementCooldown.cooldownCounter < m_MovementCooldown.cooldownDuration)
	{
		m_MovementCooldown.cooldownCounter += deltaTime;
		return true;
	}
	return false;
}

bool dae::AIBaseComponent::IsInSpawnCooldown(float deltaTime, GameObject& object)
{
	if (m_SpawnCooldown.cooldownCounter < m_SpawnCooldown.cooldownDuration)
	{
		m_SpawnCooldown.cooldownCounter += deltaTime;
		return true;
	}
	object.SetRenderStatus(true);
	return false;
}

void dae::AIBaseComponent::NextTexture()
{
	m_IndexTexturesNames++;
}


std::string dae::AIBaseComponent::GetTxt()
{
	return m_VecTextureNames[m_IndexTexturesNames];
}


dae::AxialCoordinates dae::AIBaseComponent::GetCoordinates() const
{
	return { m_Row, m_Collum };
}

dae::GameObject* dae::AIBaseComponent::GetPQBertObject() const
{
	return m_QbertObject;
}

void dae::AIBaseComponent::SetCoordinates(AxialCoordinates coordinates)
{
	m_Row = coordinates.row;
	m_Collum = coordinates.collum;
}







