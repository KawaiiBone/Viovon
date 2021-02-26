#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"

#include "Subject.h"

dae::HealthComponent::HealthComponent(int maxHp):
m_Health(maxHp), m_MaxHealth(maxHp), m_Text{  "HP: " + std::to_string(maxHp) }
{
	
}

void dae::HealthComponent::Update(float deltaTime, GameObject& object)
{
	//if (m_Health <= 0)
	//{
	//	std::make_shared<GameObject> tmp = object;
	//	//object.GetSubject().Notify((tmp), eventObeserver::died);
	//	//object.Die();
	//	//Subject::GetInstance().Notify(object, eventObeserver::died);
	//	deltaTime;
	//}
	deltaTime;
	object;
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
	object->GetSubject().Notify(object, eventObeserver::healthChanged);

	if (m_Health <= 0)
	{
		object->GetSubject().Notify(object, eventObeserver::died);
	}
	
	//Subject::GetInstance().Notify(*object, eventObeserver::healthChanged);
}


