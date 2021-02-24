#include "MiniginPCH.h"
#include "PlayerMovement.h"
#include "GameObject.h"

dae::PlayerMovement::PlayerMovement()
	: m_Text("0"),
	m_MoveLeft(false),
	m_MoveRight(false)
{
}

void dae::PlayerMovement::Update(float deltaTime, GameObject& object)
{


	object.SetMovementXAxis(object.GetVelocity()*deltaTime);

}

std::string dae::PlayerMovement::GetTxt()
{
	return m_Text;
}

void dae::PlayerMovement::MoveLeft()
{
	m_MoveLeft = true;
}

void dae::PlayerMovement::MoveRight()
{
	m_MoveRight = true;
}
