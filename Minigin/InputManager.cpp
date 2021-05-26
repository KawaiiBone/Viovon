#include "MiniginPCH.h"
#include "InputManager.h"
#include <climits>
#include "Command.h"
#include <SDL.h>


dae::InputManager::InputManager(std::vector< std::pair<Command*, OperateKey>> pcommandsVec)
	: m_ControllerID(0),
	m_pQuitCommand{ new Quit() },
	m_PlayedIndex{ 0 },
	m_Player1UsesKeyboard{ false },
	m_SaidWarning{false}

{


	ZeroMemory(&m_State, sizeof(XINPUT_STATE));

	if (!IsConnected())
	{
		std::cout << "controller is not connected!\n";
	}
	else
	{
		std::cout << "controller is connected!\n";
	}
}

dae::InputManager::InputManager()
	:m_ControllerID(0),
	m_pQuitCommand{ new Quit() },
	m_PlayedIndex{ 0 },
	m_SaidWarning{ false }

{

	ZeroMemory(&m_State, sizeof(XINPUT_STATE));

	if (!IsConnected())
	{

		std::cout << "controller is not connected!\n";
	}
	else
	{
		std::cout << "controller is connected!\n";
	}
}

dae::InputManager::~InputManager()
{

}



std::vector<std::shared_ptr<dae::Command>> dae::InputManager::ProcessInput(int index)
{
	m_ControllerID = index;
	m_PlayedIndex = index;
	std::vector<std::shared_ptr<dae::Command>> tmpCommandsVec{};
	
	SDL_Event e;
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
		{
			tmpCommandsVec.push_back(m_pQuitCommand);
		}
		if (pStates[SDL_SCANCODE_ESCAPE])
		{
			tmpCommandsVec.push_back(m_pQuitCommand);
		}
		if (Player1UsesKeyboard())
		{
			for (std::pair<UINT, std::shared_ptr<Command>>& element : m_KeyBoardKeysCommands)
			{
				if (pStates[element.first])
				{
					tmpCommandsVec.push_back(element.second);
				}
			}
			return tmpCommandsVec;
		}
	}

	if (m_Player1UsesKeyboard && index > 0)
	{
		m_ControllerID--;
	}
	else if(m_Player1UsesKeyboard)
	{
		return tmpCommandsVec;
	}


	if (IsConnected())
	{
		for (auto& pCommand : m_pCommandsVector[m_PlayedIndex])
		{
			if (IsKeyUsed(pCommand))
			{
				tmpCommandsVec.push_back(pCommand.pCommand);
			}
		}
	}
	else if(!m_SaidWarning)
	{
		std::cout << "controller is not connected!\nChanging player 1 controls to keyboard!\n To fix this issue restart the game.\n";
		m_Player1UsesKeyboard = true;
		m_SaidWarning = true;
	}


	return tmpCommandsVec;

}

void dae::InputManager::AddKeyboardCommandKeys(const std::pair<UINT, std::shared_ptr<Command>>& keyCommand)
{
	m_KeyBoardKeysCommands.push_back(keyCommand);
}


void dae::InputManager::AddDefaultCommandAndKey(const OperateCommand& command)
{
	m_pCommandsVector[0].push_back(command);
	m_pCommandsVector[1].push_back(command);
	m_pCommandsVector[2].push_back(command);
	m_pCommandsVector[3].push_back(command);
}

void dae::InputManager::SetPLayerUsesKeyboard(bool usesKeyboard)
{
	m_Player1UsesKeyboard = usesKeyboard;
}

bool dae::InputManager::Player1UsesKeyboard()
{
	return m_Player1UsesKeyboard && m_PlayedIndex == 0;
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
		if (tmpIt == m_PressedDownButtonsVec[m_PlayedIndex].end())
		{
			m_PressedDownButtonsVec[m_PlayedIndex].push_back(oCommand.ControllerKey);
		}

		return false;
	}

	if (tmpIt != m_PressedDownButtonsVec[m_PlayedIndex].end())
	{
		m_PressedDownButtonsVec[m_PlayedIndex].erase(tmpIt);
		return true;
	}

	return false;


}

bool dae::InputManager::KeyStrokeDown(OperateCommand oCommand)
{
	auto tmpIt = GetButtonStored(oCommand.ControllerKey);
	if ((m_State.Gamepad.wButtons & oCommand.ControllerKey) != 0)
	{
		if (tmpIt != m_PressedDownButtonsVec[m_PlayedIndex].end())
		{
			return false;
		}
		else
		{
			m_PressedDownButtonsVec[m_PlayedIndex].push_back(oCommand.ControllerKey);
			return true;
		}
	}
	else
	{
		if (tmpIt != m_PressedDownButtonsVec[m_PlayedIndex].end())
		{
			m_PressedDownButtonsVec[m_PlayedIndex].erase(tmpIt);
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
	std::vector<UINT>::iterator it{ m_PressedDownButtonsVec[m_PlayedIndex].begin() };
	for (; it != m_PressedDownButtonsVec[m_PlayedIndex].end(); ++it)
	{
		if (*it == button)
		{
			return it;
		}
	}

	return it;

}
