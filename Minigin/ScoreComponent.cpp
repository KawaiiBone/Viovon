#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "GameObject.h"
#include "Subject.h"

dae::ScoreComponent::ScoreComponent(int maxScore) :
	m_Score(0), m_MaxScore(maxScore), m_Text{ "Score: " + std::to_string(0.f) }, m_Subject()
{

}

void dae::ScoreComponent::Update(float , GameObject& )
{

}

std::string dae::ScoreComponent::GetTxt() const
{
	return m_Text;
}

void dae::ScoreComponent::InfluenceScore(int inf, std::shared_ptr<dae::GameObject> object)
{

	if (m_Score + inf <= m_MaxScore)
	{
		m_Score += inf;
		m_Text = "Score: " + std::to_string(m_Score);
	}
	m_Subject.Notify(object, EventObserver::scoreChanged);

}

void dae::ScoreComponent::AddObserver(Observer* pObs)
{
	m_Subject.AddObserver(pObs);
}

void dae::ScoreComponent::SubjectRender() const
{
	m_Subject.Render();
}

void dae::ScoreComponent::OnPlatform(std::shared_ptr<dae::GameObject> object, bool gainedPlatform)
{
	if (gainedPlatform)
	{
		m_Subject.Notify(object, EventObserver::gainedPlatform);
	}
	else
	{
		m_Subject.Notify(object, EventObserver::lostPlatform);
	}
	
}

void dae::ScoreComponent::Reset(GameObject& /*object*/)
{
	m_Score = 0;
}



