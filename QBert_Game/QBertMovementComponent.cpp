#include "QBertMovementComponent.h"

#include "GameObject.h"

dae::QBertMovementComponent::QBertMovementComponent(GameObject* pBlockObject)
	: m_pBlockObject(pBlockObject), m_HasLostPlatform(false)
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
	return m_pBlockObject->GetComponent<BlockComponent>()->GetPlatformStatus();
}



glm::vec2 dae::QBertMovementComponent::GetNewPosition()
{
	return m_pBlockObject->GetComponent<BlockComponent>()->GetPlatformPos();
}


bool dae::QBertMovementComponent::CanHandleMovement(MovementQbert movQbert)
{
	auto tmpP = m_pBlockObject->GetComponent<BlockComponent>()->HandleQbertMovement(movQbert);
	if (tmpP)
	{
		SetBlockObject(tmpP);
		return true;
	}
	return false;
}
