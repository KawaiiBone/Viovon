﻿#include "MiniginPCH.h"
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

std::string dae::ScoreComponent::GetTxt()
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
	m_Subject.Notify(object, EventObserver::scoreChaned);

}

void dae::ScoreComponent::AddObserver(Observer* pObs)
{
	m_Subject.AddObserver(pObs);
}

void dae::ScoreComponent::SubjectRender() const
{
	m_Subject.Render();
}



