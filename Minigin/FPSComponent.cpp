#include "MiniginPCH.h"
#include "FPSComponent.h"
#include <numeric>
#include "GameObject.h"

dae::FPSComponent::FPSComponent() :
	m_Text{ "FPS " }, counter{ 0.f }
{
}

void dae::FPSComponent::Update(float deltaTime, GameObject& ) //<- VERY IMPORTANT TO KNOW
{
	if (counter >= 1.f)
	{

		auto fPS = (std::accumulate(numbersVec.begin(), numbersVec.end(), 0.0) / numbersVec.size());//found getting the average on stack overflow by  1870232/p0w
		// link: https://stackoverflow.com/questions/28574346/find-average-of-input-to-vector-c/28574413
		
		m_Text = "FPS " + std::to_string(int(fPS));
		numbersVec.clear();
		counter = 0.f;
	}
	else
	{
		numbersVec.push_back(1 / deltaTime);
		counter += deltaTime;
	}
}

std::string dae::FPSComponent::GetTxt()
{
	return m_Text;
}



