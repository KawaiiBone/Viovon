#pragma once

#define NOMINMAX
#include  <vector>
#include "Windows.h"
#include  "Xinput.h"
#include "Singleton.h"

namespace dae
{
	enum class OperateKey;
	class Command;
	struct OperateCommand;
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager(std::vector<std::pair<Command*, OperateKey>> pcommandsVec);
		InputManager();
		~InputManager();
		Command* ProcessInput();
		void AddControllerCommand(std::pair<Command*, OperateKey> command );
		
		void AddCommandAndKey(OperateCommand command);
		
		void AddKeyboardCommand(std::pair<Command*, OperateKey> command);
		void AddController();

	private:





		
		bool IsConnected();
		bool IsPressed(OperateCommand oCommand) const;
		bool IsKeyUsed(OperateCommand oCommand);
		bool KeyStrokeUp(OperateCommand oCommand);
		bool KeyStrokeDown(OperateCommand oCommand);

	
		
		
		std::vector<UINT>::iterator GetButtonStored(UINT button);
		
		UINT m_ControllerID;
		XINPUT_STATE m_State;
		std::vector<OperateCommand>m_pCommandsVector;
		std::vector<UINT> m_PressedDownButtons;
		Command* m_pQuitCommand;
		Command* m_pDieCommand;//temporary

		//	XINPUT_STATE m_CurrentState{};
	};



}