#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class Obserer;
	class LivesComponent : public  BaseComponent
	{
	public:
		LivesComponent(int maxLives);
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void InfluenceLife(int inf, std::shared_ptr<dae::GameObject> object);
		void AddObserver(Observer* pObs);
		void SubjectRender()const override;
	
	private:
		int m_Lives;
		const int m_MaxLives;
		std::string m_Text;
		Subject m_Subject;

	};
}