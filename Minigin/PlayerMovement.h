#pragma once
#include "BaseComponent.h"

namespace dae
{
	class PlayerMovement: public  BaseComponent
	{
	public:
		PlayerMovement();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void MoveLeft();
		void MoveRight();
	private:
		std::string m_Text;
		bool m_MoveRight;
		bool m_MoveLeft;
		

		
	};
}