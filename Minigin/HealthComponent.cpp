#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"

#include "Subject.h"

dae::HealthComponent::HealthComponent(int maxHp):
m_Health(maxHp), m_MaxHealth(maxHp), m_Text{  "HP: " + std::to_string(maxHp) }
{
	
}

void dae::HealthComponent::Update(float , GameObject& )
{

}

std::string dae::HealthComponent::GetTxt()
{
	return m_Text;
}

void dae::HealthComponent::InfluenceHealth(int inf, std::shared_ptr<dae::GameObject> object)
{

	if (m_Health + inf <= m_MaxHealth)
	{
		m_Health += inf;
		m_Text =  "HP: " + std::to_string(m_Health);
	}
	object->GetSubject().Notify(object, EventObeserver::healthChanged);

	if (m_Health <= 0)
	{
		object->GetSubject().Notify(object, EventObeserver::died);
	}
	
	//Subject::GetInstance().Notify(*object, EventObeserver::healthChanged);
}


