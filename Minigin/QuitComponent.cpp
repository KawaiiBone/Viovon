#include "MiniginPCH.h"
#include "QuitComponent.h"
#include "GameObject.h"

dae::QuitComponent::QuitComponent():
m_Text("0"),m_ContinueGame(true)
{
}

void dae::QuitComponent::Update(float , GameObject& )
{
	

}

std::string dae::QuitComponent::GetTxt() const
{
	return m_Text;
}

void dae::QuitComponent::Quit()
{
	m_ContinueGame = false;
}

bool dae::QuitComponent::ContinueGame() const
{
	return m_ContinueGame;
}

void dae::QuitComponent::SubjectRender() const
{
}

void dae::QuitComponent::Reset(GameObject& /*object*/)
{
}
