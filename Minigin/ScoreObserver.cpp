#include "MiniginPCH.h"
#include "ScoreObserver.h"
#include "GameObject.h"
#include "ComponentsHeaders.h"


dae::ScoreObserver::ScoreObserver(std::pair< Transform, RenderComponent*> pRenderComScore)
	: m_pScoreComp(pRenderComScore)
{

}


dae::ScoreObserver::~ScoreObserver()
{
	delete m_pScoreComp.second;
	m_pScoreComp.second = nullptr;
}

void dae::ScoreObserver::OnNotify(std::shared_ptr<dae::GameObject> entity, EventObeserver event)
{
	switch (event) {
	case EventObeserver::scoreChaned:
		m_pScoreComp.second->Update(entity->GetComponent<ScoreComponent>()->GetTxt());
		break;
	case EventObeserver::defeatingCoily:
		//gets through when coily is defeated
		break;
	case EventObeserver::flyingDisc:
		//gets through when usin a flyingDisc
		break;
	case EventObeserver::catchingSlickAndSam:
		//gets through when catchingSlickAndSam 
		break;
	case EventObeserver::remainingDisc:
		//gets through when there are at the end  any remainingDisc
		break;
	case EventObeserver::none:
		break;
	default:;
	}
}

void dae::ScoreObserver::Render() const
{
	m_pScoreComp.second->Render(m_pScoreComp.first.GetPosition().x, m_pScoreComp.first.GetPosition().y);

}