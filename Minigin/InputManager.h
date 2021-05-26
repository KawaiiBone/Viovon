#pragma once

#define NOMINMAX
#include  <vector>
#include "Windows.h"
#include  "Xinput.h"
#include "Singleton.h"

namespace dae
{
	class Command;
	//typedef unsigned int UINT;


	enum class OperateKey
	{
		pressedDown,
		keyStrokeDown,
		keyStrokeUp

	};


	struct OperateCommand
	{
		std::shared_ptr<Command> pCommand;
		OperateKey operateKey;
		UINT ControllerKey;
	};


	enum  ControllerButton
	{
		XButton = 0x4000,
		YButton = 0x8000,
		AButton = 0x1000,
		BButton = 0x2000,
		LeftButton = 0x0004,
		RightButton = 0x0008,
		UpButton = 0x0001,
		DownButton = 0x0002,
		R1Button = 0x0200,
		L1Button = 0x0100,
		R2Button = 0x0080,
		L2Button = 0x0040,
		StartButton = 0x0010,
		BackButton = 0x0020,
		none,
	};
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager(std::vector<std::pair<Command*, OperateKey>> pcommandsVec);
		InputManager();
		~InputManager();
		std::vector<std::shared_ptr<Command>> ProcessInput(int index);


		void AddKeyboardCommandKeys(const std::pair<UINT, std::shared_ptr<Command>>& keyCommand);
		void AddDefaultCommandAndKey(const OperateCommand& command);
		void SetPLayerUsesKeyboard(bool usesKeyboard);

	private:
		bool Player1UsesKeyboard();
		bool IsConnected();
		bool IsPressed(OperateCommand oCommand) const;
		bool IsKeyUsed(OperateCommand oCommand);
		bool KeyStrokeUp(OperateCommand oCommand);
		bool KeyStrokeDown(OperateCommand oCommand);
		std::vector<UINT>::iterator GetButtonStored(UINT button);
		
		UINT m_ControllerID;
		XINPUT_STATE m_State;
		std::vector<std::vector<UINT>> m_PressedDownButtonsVec{ {},{},{},{} };
		std::vector<std::vector<OperateCommand>> m_pCommandsVector{ {},{},{},{} };
		std::shared_ptr<Command> m_pQuitCommand;
		int m_PlayedIndex;
		bool m_Player1UsesKeyboard;
		std::vector<std::pair<UINT, std::shared_ptr<Command>>> m_KeyBoardKeysCommands;
		bool m_SaidWarning;
		std::string m_HasConnectedText;
		std::string m_HasConnectedtext;
		std::string m_HasNotConnectedtext;
		std::string m_ChangeControlsText;
		
	};



}