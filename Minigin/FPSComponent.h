#pragma once
#include "BaseComponent.h"

namespace dae
{
	class FPSComponent final: public BaseComponent
	{
	public:
		FPSComponent();
		void Update(float deltaTime, GameObject& object) override;
		 std::string GetTxt()const override;
		 void SubjectRender()const override;
		 void Reset(GameObject& object) override;
	private:
		std::string m_Text;
		float counter;
		std::vector<float> numbersVec;
	};
}