#include "MiniginPCH.h"
#include "PlayerMovement.h"
#include "GameObject.h"

dae::PlayerMovement::PlayerMovement()
	: m_Text("0")

{
}

void dae::PlayerMovement::Update(float deltaTime, GameObject& object)
{


	object.SetMovement(object.GetVelocity().GetPosition().x*deltaTime, object.GetVelocity().GetPosition().y * deltaTime);
	object.SetVelocity(Transform{0 ,0,0.f });
}

std::string dae::PlayerMovement::GetTxt()
{
	return m_Text;
}


