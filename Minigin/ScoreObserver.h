#pragma once
#include "Observer.h"
#include "Transform.h"

namespace dae
{
	class RenderComponent;
	class GameObject;
	enum class eventObeserver;
	
	class ScoreObserver : public Observer
	{
	public:
		ScoreObserver(std::pair< Transform, RenderComponent*> pRenderComScore);
		~ScoreObserver();
		void OnNotify(std::shared_ptr<dae::GameObject> entity, eventObeserver event) override;
		void Render() const override;
	private:
		std::pair< Transform, RenderComponent*> m_pScoreComp;
	};
}