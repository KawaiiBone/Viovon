#pragma once
#include "Observer.h"
#include "Transform.h"


namespace dae
{
	class RenderComponent;
	class GameObject;
	enum class EventObserver;
	
	
	class ScoreObserver : public Observer
	{
	public:
		ScoreObserver(const StationaryRenderComponent& pRenderComScore);
		~ScoreObserver();
		void OnNotify(std::shared_ptr<dae::GameObject> entity, EventObserver event) override;
		void Render() const override;
	private:
		StationaryRenderComponent m_pScoreComp;

	};
}