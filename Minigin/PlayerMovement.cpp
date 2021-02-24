#include "MiniginPCH.h"
#include "PlayerMovement.h"
#include "GameObject.h"

dae::PlayerMovement::PlayerMovement()
	: m_Text("0")

{
}

void dae::PlayerMovement::Update(float deltaTime, GameObject& object)
{


	object.SetMovement(object.GetXAxisVelocity()*deltaTime, object.GetYAxisVelocity() * deltaTime);
	object.SetXAxisVelocity(0.f);
	object.SetYAxisVelocity(0.f);
}

std::string dae::PlayerMovement::GetTxt()
{
	return m_Text;
}


