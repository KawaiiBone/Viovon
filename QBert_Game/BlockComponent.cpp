#include "BlockComponent.h"

#include <functional>
#include "QBertMovementComponent.h"

#include "GameObject.h"

dae::BlockComponent::BlockComponent(float x, float y, const std::vector<MovementPosBlock>& movPosBlocksVec, const std::vector<std::string>& textureBlockNames, bool HasBlockpenalty)
	: m_PlatformPos(x,y),
	m_MovPosBlocksVec(movPosBlocksVec),
	m_TextureBlockNames(textureBlockNames),
	m_NamesVecIndex(0),
	M_HasBlockPenalty(HasBlockpenalty),
	m_platformStatus(PlatformStatus::none)
{
}

dae::BlockComponent::~BlockComponent()//gives no memory leaks
{

}

void dae::BlockComponent::Update(float , GameObject& )
{
}

std::string dae::BlockComponent::GetTxt()
{
	return m_TextureBlockNames[m_NamesVecIndex];
}

void dae::BlockComponent::SubjectRender() const
{
}

glm::vec2 dae::BlockComponent::GetPlatformPos() const
{
	return m_PlatformPos;
}

dae::GameObject* dae::BlockComponent::HandleQbertMovement(MovementQbert movQbert)
{
	for (MovementPosBlock element : m_MovPosBlocksVec)
	{
		if (element.MovQbert == movQbert)
		{
			if (!M_HasBlockPenalty)
			{
				element.pBlockObject->GetComponent<BlockComponent>()->NextBlockTexture();
			}
			else
			{
				element.pBlockObject->GetComponent<BlockComponent>()->ThirdLvlChangeBlockTexture();
			}
			
			return element.pBlockObject;	
		}
	}
	return nullptr;
}

void dae::BlockComponent::AddMovementPosBlock(const MovementPosBlock& MovPosBlock)
{
	m_MovPosBlocksVec.push_back(MovPosBlock);
}

void dae::BlockComponent::NextBlockTexture()
{
	if (size_t(m_NamesVecIndex+1) < m_TextureBlockNames.size())
	{
		m_NamesVecIndex++;
		m_platformStatus = PlatformStatus::gainedStatus;
	}
	else
	{
		m_platformStatus = PlatformStatus::none;
	}
}
void dae::BlockComponent::ThirdLvlChangeBlockTexture()
{
	if (m_NamesVecIndex > 0)
	{
		m_NamesVecIndex--;
		m_platformStatus = PlatformStatus::lostStatus;
	}
	else
	{
		m_NamesVecIndex++;
		m_platformStatus = PlatformStatus::gainedStatus;
	
	}
}

dae::PlatformStatus dae::BlockComponent::GetPlatformStatus()
{
	return m_platformStatus;
}
