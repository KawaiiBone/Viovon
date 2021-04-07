#pragma once
#include "BaseComponent.h"

namespace dae
{
	class FPSComponent final: public BaseComponent
	{
	public:
		FPSComponent();
		void Update(float deltaTime, GameObject& object) override;
		 std::string GetTxt() override;
		 void SubjectRender()const override;
	private:
		std::string m_Text;
		float counter;
		std::vector<float> numbersVec;
	};
}