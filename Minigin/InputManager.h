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
		std::shared_ptr<Command> ProcessInput(int index);
		
		void AddCommandAndKey(const OperateCommand& command);
		

	private:





		
		bool IsConnected();
		bool IsPressed(OperateCommand oCommand) const;
		bool IsKeyUsed(OperateCommand oCommand);
		bool KeyStrokeUp(OperateCommand oCommand);
		bool KeyStrokeDown(OperateCommand oCommand);

	
		
		
		std::vector<UINT>::iterator GetButtonStored(UINT button);
		
		UINT m_ControllerID;
		XINPUT_STATE m_State;
		//std::vector<OperateCommand>m_pCommandsVector;
	//	std::vector<UINT> m_PressedDownButtonsVec;
		std::vector<std::vector<UINT>> m_PressedDownButtonsVec{ {},{},{},{} };
		std::vector<std::vector<OperateCommand>> m_pCommandsVector{ {},{},{},{} };
		std::shared_ptr<Command> m_pQuitCommand;
		std::shared_ptr<Command> m_pDieCommand;//temporary
		int m_PlayedIndex;

		//	XINPUT_STATE m_CurrentState{};
	};



}