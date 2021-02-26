#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "GameObject.h"

#include "Subject.h"

dae::ScoreComponent::ScoreComponent(int maxScore) :
	m_Score(0), m_MaxScore(maxScore), m_Text{ "Score: " + std::to_string(0.f) }
{

}

void dae::ScoreComponent::Update(float deltaTime, GameObject& object)
{
	return;
	object;
	deltaTime;
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
	object->GetSubject().Notify(object, eventObeserver::scoreChaned);
	//Subject::GetInstance().Notify(*object, eventObeserver::healthChanged);
}