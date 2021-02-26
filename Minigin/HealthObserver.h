#pragma once
#include "Observer.h"
#include "Transform.h"

namespace dae
{
	class RenderComponent;
	class GameObject;
	enum class eventObeserver;
	class HealthObserver : public Observer
	{
	public:
		HealthObserver(std::pair< Transform, RenderComponent*> pRenderComHealth, std::pair< Transform, RenderComponent*> pRenderComDead);
		~HealthObserver();
		void OnNotify(std::shared_ptr<dae::GameObject>, eventObeserver event) override;
		void Render() const override;
	private:
		std::pair< Transform, RenderComponent*> m_pHealthRenderComp;
		std::pair< Transform, RenderComponent*> m_pDeadRenderComp;
		bool m_PlayerDied;
	};
}
