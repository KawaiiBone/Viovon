﻿#include "MiniginPCH.h"
#include "PlayerMovement.h"
#include "GameObject.h"

dae::PlayerMovement::PlayerMovement()
	: m_Text("0")

{
}

void dae::PlayerMovement::Update(float , GameObject& )
{



}

std::string dae::PlayerMovement::GetTxt() const
{
	return m_Text;
}

void dae::PlayerMovement::SubjectRender() const
{
}

void dae::PlayerMovement::Reset(GameObject& /*object*/)
{
}


