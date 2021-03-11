#pragma once
#include "Observer.h"
#include "Transform.h"

namespace dae
{
	class RenderComponent;
	class GameObject;
	enum class EventObserver;
	class HealthObserver : public Observer
	{
	public:
		HealthObserver(std::pair< Transform, RenderComponent*> pRenderComHealth, std::pair< Transform, RenderComponent*> pRenderComDead);
		~HealthObserver();
		void OnNotify(std::shared_ptr<dae::GameObject>, EventObserver event) override;
		void Render() const override;
	private:
		std::pair< Transform, RenderComponent*> m_pHealthRenderComp;
		std::pair< Transform, RenderComponent*> m_pDeadRenderComp;
		bool m_PlayerDied;
	};
}
