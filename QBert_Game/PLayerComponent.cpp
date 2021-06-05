#include "PLayerComponent.h"
#include "Scene.h"
#include "GameObject.h"
#include "MapBlockComponent.h"
#include "ServiceLocater.h"

dae::PLayerComponent::PLayerComponent(GameObject* pBlockObject, int row, int collum, const std::string& soundPath)
	: m_pBlockObject(pBlockObject),
	m_Row(row),
	m_Collum(collum),
	m_MovementCooldown{ 0.35f,0.f, true },
	m_Text{"0"},
	m_StartingRow(row),
	m_StartingCollum(collum),
	m_SoundPath(soundPath),
	m_Volume(10),
	m_OldRow(row),
	m_OldCollum(collum)
{

}

dae::PLayerComponent::~PLayerComponent()
{
	/*delete m_pBlockObject;
	m_pBlockObject = nullptr;*/
}

void dae::PLayerComponent::Update(float delta, GameObject&)
{
	if (m_MovementCooldown.cooldownCounter < m_MovementCooldown.cooldownDuration)
	{
		m_MovementCooldown.cooldownCounter += delta;

	}
	else
	{
		m_MovementCooldown.cooldownOver = true;
	}


}

void dae::PLayerComponent::SetBlockObject(GameObject* pBlockObject)
{

	m_pBlockObject = pBlockObject;
}

void dae::PLayerComponent::Reset(GameObject& object)
{
	auto* tmplock = SceneManager::GetInstance().GetCurrentScene()->GetMapPart(m_StartingRow, m_StartingCollum).second;
	SetBlockObject(tmplock);
	object.SetPosition(tmplock->GetComponent<MapBlockComponent>()->GetPlatformPos().x, tmplock->GetComponent<MapBlockComponent>()->GetPlatformPos().y);
	m_Row = m_StartingRow;
	m_Collum = m_StartingCollum;
	
}

void dae::PLayerComponent::PLaySound() const
{
	ServiceLocater::GetSoundSystem().PlaySound(m_SoundPath, m_Volume);
}

void dae::PLayerComponent::ResetCooldown()
{
	m_MovementCooldown.cooldownOver = false;
	m_MovementCooldown.cooldownCounter = 0.f;
}




std::string dae::PLayerComponent::GetTxt() const
{
	return m_Text;
}

void dae::PLayerComponent::SubjectRender() const
{
}

dae::PlatformStatus dae::PLayerComponent::GetPlatformStatus()
{
	return m_pBlockObject->GetComponent<MapPartComponent>()->GetPlatformStatus();
}

dae::AxialCoordinates dae::PLayerComponent::GetCoordinates() const
{
	return { m_Row,m_Collum };
}

dae::AxialCoordinates dae::PLayerComponent::GetOldCoordinates() const
{
	return { m_OldRow,m_OldCollum };
}

void dae::PLayerComponent::SetCoordinates(AxialCoordinates coordinates)
{
	m_OldRow = m_Row;
	m_OldCollum = m_Collum;
	m_Row = coordinates.row;
	m_Collum = coordinates.collum;
}

bool dae::PLayerComponent::IsMovementCooldownOver()
{
	return m_MovementCooldown.cooldownOver;
}




glm::vec2 dae::PLayerComponent::GetNewPosition()
{
	return m_pBlockObject->GetComponent<MapPartComponent>()->GetPlatformPos();
	//return m_pBlockObject->GetComponent<MapBlockComponent>()->GetPlatformPos();

}


bool dae::PLayerComponent::CanHandleMovement(GameObject* movQber)
{
	//auto tmpP = m_pBlockObject->GetComponent<MapBlockComponent>()->HandleQbertMovement(movQbert);
	auto tmpP = m_pBlockObject->GetComponent<MapPartComponent>()->HandleQbertMovement(movQber);
	if (tmpP)
	{
		m_MovementCooldown.cooldownOver = false;
		m_MovementCooldown.cooldownCounter = 0.f;
		SetBlockObject(tmpP);
		return true;
	}
	return false;
}
