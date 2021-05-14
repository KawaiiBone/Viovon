#include "MapPartComponent.h"

#include <functional>
#include "QBertMovementComponent.h"

#include "GameObject.h"

dae::MapPartComponent::MapPartComponent(float x, float y, const std::vector<std::string>& textureBlockName, bool isblock)
	: m_PlatformPos(x, y),
	m_TextureBlockNames(textureBlockName),
	m_NamesVecIndex(0),
	m_IsBlock(isblock)

{
}

dae::MapPartComponent::~MapPartComponent()//gives no memory leaks
{

}

void dae::MapPartComponent::Update(float, GameObject&)
{
}

std::string dae::MapPartComponent::GetTxt()
{
	return m_TextureBlockNames[m_NamesVecIndex];
}

void dae::MapPartComponent::SubjectRender() const
{
}

glm::vec2 dae::MapPartComponent::GetPlatformPos() const
{
	return m_PlatformPos;
}

dae::GameObject* dae::MapPartComponent::HandleQbertMovement(GameObject* movQbert)
{
	if (movQbert->GetComponent<MapPartComponent>()->IsBlock())
	{
		ChangeMovementPosBlock(movQbert);
		return movQbert;
	}
	else
	{
		return movQbert->GetComponent<MapPartComponent>()->HandleQbertMovement(movQbert);
		//m_PlatformStatus = PlatformStatus::none;
		
	}

}





dae::PlatformStatus dae::MapPartComponent::GetPlatformStatus()
{
	return m_PlatformStatus;
}

bool dae::MapPartComponent::PlusNamesVecIndex()
{
	if ( size_t(m_NamesVecIndex + 1) < m_TextureBlockNames.size() )
	{
		m_NamesVecIndex++;
		return true;
	}
	return false;
}

bool dae::MapPartComponent::MinusNamesVecIndex()
{
	if (m_NamesVecIndex > 0)
	{
		m_NamesVecIndex--;
		return true;
	}
	return false;
}

void dae::MapPartComponent::SetPlatformStatus(PlatformStatus platStatus)
{
	m_PlatformStatus = platStatus;
}

bool dae::MapPartComponent::IsBlock()
{
	return m_IsBlock;
}
