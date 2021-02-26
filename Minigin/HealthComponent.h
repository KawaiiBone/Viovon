#pragma once
#include "BaseComponent.h"

namespace dae
{
	class HealthComponent : public  BaseComponent
	{
	public:
		HealthComponent(int maxHp);
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void InfluenceHealth(int inf, std::shared_ptr<dae::GameObject> object);
	private:
		int m_Health;
		const int m_MaxHealth;
		std::string m_Text;


	};
}