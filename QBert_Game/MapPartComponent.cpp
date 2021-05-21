#include "MapPartComponent.h"

#include <functional>
#include "QBertMovementComponent.h"

#include "GameObject.h"

dae::MapPartComponent::MapPartComponent(float x, float y, float width, float height, const std::vector<std::string>& textureBlockName, bool isblock, bool penalty)
	: m_PlatformPos(x+ width / 4, y- height / 5),
	m_TextureBlockNames(textureBlockName),
	m_NamesVecIndex(0),
	m_IsBlock(isblock),
	m_WrongwayPlatformPos(x+ width/1.45f,y+height/1.45f),
	m_UggPlatformPos(x- width/6, y+width/2),
	m_Penalty(penalty)

{

}

dae::MapPartComponent::~MapPartComponent()//gives no memory leaks
{

}

void dae::MapPartComponent::Update(float, GameObject&)
{
}

std::string dae::MapPartComponent::GetTxt() const
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

	}

}

void dae::MapPartComponent::HandleAiMovement()
{


	if (MinusNamesVecIndex())
	{
		m_PlatformStatus = PlatformStatus::lostStatus;
	}
	else
	{
		m_PlatformStatus = PlatformStatus::none;
	}


}


dae::PlatformStatus dae::MapPartComponent::GetPlatformStatus() const
{
	return m_PlatformStatus;
}

bool dae::MapPartComponent::PlusNamesVecIndex()
{
	if (size_t(m_NamesVecIndex + 1) < m_TextureBlockNames.size())
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

bool dae::MapPartComponent::HasPenalty()
{
	return m_Penalty;
}

bool dae::MapPartComponent::IsBlock() 
{
	return m_IsBlock;
}

glm::vec2 dae::MapPartComponent::GetUggPlatformPos() const
{
	return m_UggPlatformPos;
}

glm::vec2 dae::MapPartComponent::GetWrongWayPlatformPos() const
{
	return m_WrongwayPlatformPos;
}

void dae::MapPartComponent::Reset(GameObject& /*object*/)
{
	m_NamesVecIndex = 0;
}

bool dae::MapPartComponent::PlatformDone() const
{
	return size_t(m_NamesVecIndex + 1) >= m_TextureBlockNames.size();
}
