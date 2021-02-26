#pragma once
#include "BaseComponent.h"

namespace dae
{
	class ScoreComponent : public  BaseComponent
	{
	public:
		ScoreComponent(int maxScore);
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void InfluenceScore(int inf, std::shared_ptr<dae::GameObject> object);
	private:
		int m_Score;
		const int m_MaxScore;
		std::string m_Text;


	};
}