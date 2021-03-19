#pragma once
#include "Observer.h"
#include "Transform.h"

namespace dae
{


	class RenderComponent;
	class GameObject;
	enum class EventObserver;
	class LivesObserver : public Observer
	{
	public:
		LivesObserver(const StationaryRenderComponent& m_pStationHealthRenderComp, const StationaryRenderComponent& m_pStationDeadRenderComp);
		~LivesObserver();
		void OnNotify(std::shared_ptr<dae::GameObject>, EventObserver event) override;
		void Render() const override;
	private:
		StationaryRenderComponent m_pStationLivesRenderComp;
		StationaryRenderComponent m_pDeadRenderComp;
		bool m_PlayerDied;
	};
}
