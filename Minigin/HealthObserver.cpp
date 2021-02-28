#include "MiniginPCH.h"
#include "HealthObserver.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "HealthComponent.h"


dae::HealthObserver::HealthObserver(std::pair< Transform, RenderComponent*> pRenderComHealth, std::pair< Transform, RenderComponent*> pRenderComDead)
	: m_pHealthRenderComp(pRenderComHealth), m_pDeadRenderComp(pRenderComDead), m_PlayerDied{ false }
{

}


dae::HealthObserver::~HealthObserver()
{
	delete m_pHealthRenderComp.second;
	delete m_pDeadRenderComp.second;
	m_pHealthRenderComp.second = nullptr;
	m_pDeadRenderComp.second = nullptr;
}

void dae::HealthObserver::OnNotify(std::shared_ptr<dae::GameObject> entity, EventObeserver event)
{
	switch (event) {
	case EventObeserver::died:
		entity->IsDead();//update here
		m_PlayerDied = true;
		break;
	case EventObeserver::healthChanged:
		m_pHealthRenderComp.second->Update(entity->GetComponent<HealthComponent>()->GetTxt());
		break;
	case EventObeserver::none:
		break;
	default:;
	}
}

void dae::HealthObserver::Render() const
{
	m_pHealthRenderComp.second->Render(m_pHealthRenderComp.first.GetPosition().x, m_pHealthRenderComp.first.GetPosition().y);
	if (m_PlayerDied)
	{
		m_pDeadRenderComp.second->Render(m_pDeadRenderComp.first.GetPosition().x, m_pDeadRenderComp.first.GetPosition().y);
	}
}