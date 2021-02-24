
namespace dae
{
	enum class OperateKey
	{
		pressedDown,
		keyStrokeDown,
		keyStrokeUp

	};

	class Command;
	typedef unsigned int UINT;
	
	struct OperateCommand
	{
		Command* pCommand;
		OperateKey operateKey;
		UINT ControllerKey;
	};
}