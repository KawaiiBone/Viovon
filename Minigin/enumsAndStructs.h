//#define XINPUT_GAMEPAD_DPAD_UP          0x0001
//#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002
//#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004
//#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
//#define XINPUT_GAMEPAD_START            0x0010
//#define XINPUT_GAMEPAD_BACK             0x0020
//#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040
//#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
//#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
//#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
//#define XINPUT_GAMEPAD_A                0x1000
//#define XINPUT_GAMEPAD_B                0x2000
//#define XINPUT_GAMEPAD_X                0x4000
//#define //XINPUT_GAMEPAD_Y                0x8000


namespace dae
{
  #define Invalid_String std::string{""}


	
	class Command;
	typedef unsigned int UINT;

	
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




	enum class EventObeserver
	{
		died,
		healthChanged,
		scoreChaned,
		defeatingCoily,
		flyingDisc,
		remainingDisc,
		catchingSlickAndSam,
		none,
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




	enum class InterFaceNames
	{
		start,
		howToPlay,
		buttons,
		modes,
		none,
	};

	

	
	
	

	
}