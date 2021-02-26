
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
		std::shared_ptr<Command> pCommand;
		OperateKey operateKey;
		UINT ControllerKey;
	};




	enum class eventObeserver
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
}