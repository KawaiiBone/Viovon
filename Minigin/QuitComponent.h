#pragma once
#include "BaseComponent.h"

namespace dae
{
	class QuitComponent : public BaseComponent
	{
	public:
		QuitComponent();
		void Update(float deltaTime) override;
		std::string GetTxt() override;
		void Quit();
		bool ContinueGame() const;
	private:
		std::string m_Text;
		bool m_ContinueGame;
	};
}