#pragma once

#define NOMINMAX
#include  <vector>
#include "Windows.h"
#include  "Xinput.h"
#include "Singleton.h"

namespace dae
{
	class Command;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager(std::vector<std::pair<Command*, bool>> pcommandsVec);
		InputManager();
		~InputManager();
		Command* ProcessInput();
		void AddCommand(std::pair<Command*, bool> command );
		void AddController();

	private:

		bool IsConnected();
		bool IsPressed(UINT button) const;
		bool IsKeyUsed(UINT button, bool keyDown);
		std::vector<UINT>::iterator GetButtonStored(UINT button);
		
		UINT m_ControllerID;
		XINPUT_STATE m_State;
		std::vector<std::pair<Command*, bool>> m_pCommandsVec;
		std::vector<UINT> m_PressedDownButtons;
		Command* m_pQuitCommand;
		Command* m_pDieCommand;//temporary

		//	XINPUT_STATE m_CurrentState{};
	};



}