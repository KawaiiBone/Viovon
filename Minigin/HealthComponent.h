#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class Obserer;
	class HealthComponent : public  BaseComponent
	{
	public:
		HealthComponent(int maxHp);
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void InfluenceHealth(int inf, std::shared_ptr<dae::GameObject> object);
		void AddObserver(Observer* pObs);
		void SubjectRender()const override;
	
	private:
		int m_Health;
		const int m_MaxHealth;
		std::string m_Text;
		Subject m_Subject;

	};
}