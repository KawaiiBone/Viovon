#include "QBertMovementComponent.h"
#include "Scene.h"
#include "GameObject.h"

dae::QBertMovementComponent::QBertMovementComponent(GameObject* pBlockObject, int row, int collum)
	: m_pBlockObject(pBlockObject), m_Row(row), m_Collum(collum), m_MovementCooldown{0.35f,0.f, true}
{
	
}

dae::QBertMovementComponent::~QBertMovementComponent()
{
	/*delete m_pBlockObject;
	m_pBlockObject = nullptr;*/
}

void dae::QBertMovementComponent::Update(float delta , GameObject&)
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

void dae::QBertMovementComponent::SetBlockObject( GameObject* pBlockObject)
{

	m_pBlockObject = pBlockObject;
}


std::string dae::QBertMovementComponent::GetTxt()
{
	return "0";
}

void dae::QBertMovementComponent::SubjectRender() const
{
}

dae::PlatformStatus dae::QBertMovementComponent::GetPlatformStatus()
{
	return m_pBlockObject->GetComponent<MapPartComponent>()->GetPlatformStatus();
	//return m_pBlockObject->GetComponent<MapBlockComponent>()->GetPlatformStatus();
}

dae::AxialCoordinates dae::QBertMovementComponent::GetCoordinates()
{
	return { m_Row,m_Collum };
}

void dae::QBertMovementComponent::SetCoordinates(AxialCoordinates coordinates)
{
	m_Row = coordinates.row;
	m_Collum = coordinates.collum;
}

bool dae::QBertMovementComponent::IsMovementCooldownOver()
{
	return m_MovementCooldown.cooldownOver;
}




glm::vec2 dae::QBertMovementComponent::GetNewPosition()
{
	return m_pBlockObject->GetComponent<MapPartComponent>()->GetPlatformPos();
	//return m_pBlockObject->GetComponent<MapBlockComponent>()->GetPlatformPos();

}


bool dae::QBertMovementComponent::CanHandleMovement(GameObject* movQber )
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
