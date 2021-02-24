#include "MiniginPCH.h"
#include "InputManager.h"
#include <climits>
#include "Command.h"
#include <SDL.h>


dae::InputManager::InputManager(std::vector< std::pair<Command*, OperateKey>> pcommandsVec)
	: m_ControllerID(0),
	/*m_pCommandsVec(pcommandsVec),*/
	m_pQuitCommand{ new Quit() },
	m_pDieCommand(new Die())
	
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));

	if (!IsConnected())
	{
		std::cout << "controller is not connected!\n";
	}
}

dae::InputManager::InputManager()
	:m_ControllerID(0),
	m_pQuitCommand{ new Quit() },
	//m_pCommandsVec{},
	m_pDieCommand(new Die())
	
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




	for (auto pBasecommand : m_pCommandsVector)
	{
		delete pBasecommand.pCommand;
		pBasecommand.pCommand = nullptr;
	}
	m_pCommandsVector.clear();
}

dae::Command* dae::InputManager::ProcessInput()
{
	// todo: read the input

	SDL_Event e;
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) 
		{
			return m_pQuitCommand;
		}
		/*if (e.type == SDL_SCANCODE_A) {
			return m_pDieCommand;
		}*/
		if (pStates[SDL_SCANCODE_A])
		{
			return m_pDieCommand;
		}
	
	}


	if (IsConnected())
	{
		for (auto pCommand : m_pCommandsVector)
		{
			if (IsKeyUsed(pCommand))
			{
				return pCommand.pCommand;
			}
		}
	}
	else
	{
		std::cout << "controller is not connected\n!";
	}




	return nullptr;
}


void dae::InputManager::AddCommandAndKey(OperateCommand command)
{
	m_pCommandsVector.push_back(command);
}

void dae::InputManager::AddController()
{
	std::cout << "controller added!\n";
}






bool dae::InputManager::IsKeyUsed(OperateCommand oCommand)
{


	
	switch (oCommand.operateKey) {
		case OperateKey::pressedDown:
			return IsPressed(oCommand);
		break;
	case OperateKey::keyStrokeDown:
		return KeyStrokeDown(oCommand);
		break;
	case OperateKey::keyStrokeUp:
		return KeyStrokeUp(oCommand);
		break;
	}
	return false;

}
bool dae::InputManager::IsPressed(OperateCommand oCommand) const
{
	
	return (m_State.Gamepad.wButtons & oCommand.ControllerKey) != 0;

}
bool dae::InputManager::KeyStrokeUp(OperateCommand oCommand)
{
	auto tmpIt = GetButtonStored(oCommand.ControllerKey);
	if ((m_State.Gamepad.wButtons & oCommand.ControllerKey) != 0)
	{
		if (tmpIt == m_PressedDownButtons.end())
		{
			m_PressedDownButtons.push_back(oCommand.ControllerKey);
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

bool dae::InputManager::KeyStrokeDown(OperateCommand oCommand)
{
	auto tmpIt = GetButtonStored(oCommand.ControllerKey);
	if ((m_State.Gamepad.wButtons & oCommand.ControllerKey) != 0)
	{
		if (tmpIt != m_PressedDownButtons.end())
		{
			return false;
		}
		else
		{
			m_PressedDownButtons.push_back(oCommand.ControllerKey);
			return true;
		}
	}
	else
	{
		if (tmpIt != m_PressedDownButtons.end())
		{
			m_PressedDownButtons.erase(tmpIt);
		}
		return false;
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
