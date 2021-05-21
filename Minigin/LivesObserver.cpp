#include "MiniginPCH.h"
#include "LivesObserver.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "LivesComponent.h"
#include "Scene.h"
#include "SceneManager.h"




dae::LivesObserver::LivesObserver(const StationaryRenderComponent& m_pStationHealthRenderComp, const StationaryRenderComponent& m_pStationDeadRenderComp)
	: m_pStationLivesRenderComp(m_pStationHealthRenderComp), m_pDeadRenderComp(m_pStationDeadRenderComp), m_PlayerDied{ false }
{

}


dae::LivesObserver::~LivesObserver()
{
	delete m_pStationLivesRenderComp.renderComp;
	delete m_pDeadRenderComp.renderComp;
	m_pStationLivesRenderComp.renderComp = nullptr;
	m_pDeadRenderComp.renderComp = nullptr;
}

void dae::LivesObserver::OnNotify(std::shared_ptr<dae::GameObject> entity, EventObserver event)
{
	switch (event) {
	case EventObserver::died:
		SceneManager::GetInstance().GetCurrentScene()->ResetScene();
		//entity->IsDead();//update here
	//	m_PlayerDied = true;
		break;
	case EventObserver::healthChanged:
		m_pStationLivesRenderComp.renderComp->Update(entity->GetComponent<LivesComponent>()->GetTxt());
		break;
	case EventObserver::none:
		break;
	default:;
	}
}

void dae::LivesObserver::Render() const
{
	m_pStationLivesRenderComp.renderComp->Render(m_pStationLivesRenderComp.x, m_pStationLivesRenderComp.y);
	if (m_PlayerDied)
	{
		m_pDeadRenderComp.renderComp->Render(m_pDeadRenderComp.x, m_pDeadRenderComp.y);
	}
}