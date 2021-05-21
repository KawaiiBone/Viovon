#pragma once
#include "BaseComponent.h"

namespace dae
{
	class PlayerMovement final : public  BaseComponent
	{
	public:
		PlayerMovement();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() const override;
		void SubjectRender()const override;
		void Reset(GameObject& object) override;
		

	private:
		std::string m_Text;

		

		
	};
}