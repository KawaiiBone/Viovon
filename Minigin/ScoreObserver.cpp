#include "MiniginPCH.h"
#include "ScoreObserver.h"
#include "GameObject.h"
#include "ComponentsHeaders.h"


dae::ScoreObserver::ScoreObserver(const StationaryRenderComponent& pRenderComScore)
	: m_pScoreComp(pRenderComScore)
{

}


dae::ScoreObserver::~ScoreObserver()
{
	delete m_pScoreComp.renderComp;
	m_pScoreComp.renderComp = nullptr;
}

void dae::ScoreObserver::OnNotify(std::shared_ptr<dae::GameObject> entity, EventObserver event)
{
	switch (event) {
	case EventObserver::scoreChanged:
		m_pScoreComp.renderComp->Update(entity->GetComponent<ScoreComponent>()->GetTxt());
		break;
	case EventObserver::ScoreReset:
		m_pScoreComp.renderComp->Update(entity->GetComponent<ScoreComponent>()->GetTxt());
		break;
	case EventObserver::flyingDisc:
		//gets through when usin a flyingDisc
		break;
	case EventObserver::catchingSlickAndSam:
		//gets through when catchingSlickAndSam 
		break;
	case EventObserver::remainingDisc:
		//gets through when there are at the end  any remainingDisc
		break;
	case EventObserver::none:
		break;
	default:;
	}
}

void dae::ScoreObserver::Render() const
{
	m_pScoreComp.renderComp->Render(m_pScoreComp.x, m_pScoreComp.y);

}