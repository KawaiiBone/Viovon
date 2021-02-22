#pragma once
#include "BaseComponent.h"

namespace dae
{
	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent();
		void Update(float deltaTime) override;
		 std::string GetTxt() override;
	private:
		std::string m_Text;
		float counter;
		std::vector<float> numbersVec;
	};
}