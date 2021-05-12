#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class Observer;
	class ScoreComponent final : public  BaseComponent
	{
	public:
		ScoreComponent(int maxScore);
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void InfluenceScore(int inf, std::shared_ptr<dae::GameObject> object);
		void AddObserver(Observer* pObs);
		void SubjectRender()const override;
		void OnPlatform(std::shared_ptr<dae::GameObject> object, bool gainedPlatform);
	private:
		int m_Score;
		const int m_MaxScore;
		std::string m_Text;
		Subject m_Subject;

	};
}