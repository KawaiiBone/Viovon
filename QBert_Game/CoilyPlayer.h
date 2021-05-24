#pragma once
namespace dae
{

	class CoilyPlayer
	{
	public:
		CoilyPlayer(int playerIndex);
		void CreateCoily();
	private:
		const int m_PlayerIndex;

	};
}
