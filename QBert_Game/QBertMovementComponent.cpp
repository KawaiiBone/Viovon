#include "QBertMovementComponent.h"
#include "Scene.h"
#include "GameObject.h"

dae::QBertMovementComponent::QBertMovementComponent(GameObject* pBlockObject, int row, int collum)
	: m_pBlockObject(pBlockObject), m_HasLostPlatform(false), m_Row(row), m_Collum(collum)
{
	
}

dae::QBertMovementComponent::~QBertMovementComponent()
{
	/*delete m_pBlockObject;
	m_pBlockObject = nullptr;*/
}

void dae::QBertMovementComponent::Update(float , GameObject&)
{
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


glm::vec2 dae::QBertMovementComponent::GetNewPosition()
{
	return m_pBlockObject->GetComponent<MapPartComponent>()->GetPlatformPos();
	//return m_pBlockObject->GetComponent<MapBlockComponent>()->GetPlatformPos();

}


bool dae::QBertMovementComponent::CanHandleMovement(GameObject* movQbert)
{
	//auto tmpP = m_pBlockObject->GetComponent<MapBlockComponent>()->HandleQbertMovement(movQbert);
	auto tmpP = m_pBlockObject->GetComponent<MapPartComponent>()->HandleQbertMovement(movQbert);
	if (tmpP)
	{
		SetBlockObject(tmpP);
		return true;
	}
	return false;
}
