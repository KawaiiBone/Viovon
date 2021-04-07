#pragma once
#include "BaseComponent.h"

namespace dae
{
	class QuitComponent final : public BaseComponent
	{
	public:
		QuitComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void Quit();
		bool ContinueGame() const;
		void SubjectRender()const override;
	
	private:
		std::string m_Text;
		bool m_ContinueGame;
	};
}