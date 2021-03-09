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
		void SubjectRender()const override;
		

	private:
		std::string m_Text;

		

		
	};
}