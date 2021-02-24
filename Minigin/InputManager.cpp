#include "MiniginPCH.h"
#include "InputManager.h"
#include <climits>
#include "Command.h"
#include <SDL.h>


dae::InputManager::InputManager(std::vector< std::pair<Command*, bool>> pcommandsVec)
	: m_ControllerID(0),
	m_pCommandsVec(pcommandsVec),
	m_pQuitCommand{ new Quit(0) },
	m_pDieCommand(new Die(0))
	
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));

	if (!IsConnected())
	{
		std::cout << "controller is not connected!\n";
	}
}

dae::InputManager::InputManager()
	:m_ControllerID(0),
	m_pQuitCommand{ new Quit(0) },
	m_pCommandsVec{},
	m_pDieCommand(new Die(0))
	
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));

	if (!IsConnected())
	{

		std::cout << "controller is not connected!\n";
	}
}

dae::InputManager::~InputManager()
{
	delete m_pQuitCommand;
	delete m_pDieCommand;
	m_pQuitCommand = nullptr;
	m_pDieCommand = nullptr;


	for (auto pBasecommand : m_pCommandsVec)
	{
		delete pBasecommand.first;
		pBasecommand.first = nullptr;
	}
	m_pCommandsVec.clear();
}

dae::Command* dae::InputManager::ProcessInput()
{
	// todo: read the input

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) 
		{
			return m_pQuitCommand;
		}
	/*	if (e.type == SDL_KEYDOWN) {
			return m_pDieCommand;
		}*/
	
	}


	if (IsConnected())
	{
		for (auto pCommand : m_pCommandsVec)
		{
			if (IsKeyUsed(pCommand.first->GetButton(), pCommand.second))
			{
				return pCommand.first;
			}
		}
	}
	else
	{
		std::cout << "controller is not connected\n!";
	}




	return nullptr;
}

void dae::InputManager::AddCommand(std::pair<Command*, bool> command)
{
	m_pCommandsVec.push_back({ command });
}

void dae::InputManager::AddController()
{
	std::cout << "controller added!\n";
}



bool dae::InputManager::IsPressed(UINT button) const
{
	// todo: return whether the given button is pressed or not.
	return (m_State.Gamepad.wButtons & button) != 0;

}


bool dae::InputManager::IsKeyUsed(UINT button, bool keyDown)
{
	auto tmpIt = GetButtonStored(button);
	if ((m_State.Gamepad.wButtons & button) != 0)
	{
		if (keyDown)
		{
			if (tmpIt == m_PressedDownButtons.end())
			{
				m_PressedDownButtons.push_back(button);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (tmpIt == m_PressedDownButtons.end())
			{
				m_PressedDownButtons.push_back(button);
			}
			return false;
		}


	}
	else
	{

		if (keyDown)
		{
			if (tmpIt != m_PressedDownButtons.end())
			{
				m_PressedDownButtons.erase(tmpIt);
			}
			return false;
		}
		else
		{
			if (tmpIt != m_PressedDownButtons.end())
			{
				m_PressedDownButtons.erase(tmpIt);
				return true;
			}
			else
			{
				return false;
			}
		}


	}

}

bool dae::InputManager::IsConnected()
{

	if (XInputGetState(m_ControllerID, &m_State) == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<UINT>::iterator dae::InputManager::GetButtonStored(UINT button)
{
	std::vector<UINT>::iterator it{ m_PressedDownButtons.begin() };
	for (; it != m_PressedDownButtons.end(); ++it)
	{
		if (*it == button)
		{
			return it;
		}
	}

	return it;

}
