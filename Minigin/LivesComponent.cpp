#include "MiniginPCH.h"
#include "LivesComponent.h"
#include "GameObject.h"

#include "Subject.h"

dae::LivesComponent::LivesComponent(int maxLives):
	m_Lives(maxLives), m_MaxLives(maxLives), m_Text{  "Lives: " + std::to_string(maxLives) }, m_Subject{  }
{
	
}

void dae::LivesComponent::Update(float , GameObject& )
{
	
}

std::string dae::LivesComponent::GetTxt() const
{
	return m_Text;
}

void dae::LivesComponent::InfluenceLife(int inf, std::shared_ptr<dae::GameObject> object)
{

	
	if (m_Lives + inf <= m_MaxLives)
	{
		m_Lives += inf;
		m_Text =  "Lives: " + std::to_string(m_Lives);
	}
	m_Subject.Notify(object, EventObserver::healthChanged);
	if (m_Lives <= 0)
	{
		m_Subject.Notify(object, EventObserver::died);
	}
	
	//Subject::GetInstance().Notify(*object, EventObserver::healthChanged);
}


void dae::LivesComponent::AddObserver(Observer* pObs)
{
	m_Subject.AddObserver(pObs);
}

void dae::LivesComponent::SubjectRender() const
{
	m_Subject.Render();
}

void dae::LivesComponent::Reset(GameObject& /*object*/)
{
	m_Lives = m_MaxLives;
	m_Text = "Lives: " + std::to_string(m_Lives);

}
