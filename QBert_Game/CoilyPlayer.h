#pragma once
namespace dae
{

	class CoilyPlayer
	{
	public:
		CoilyPlayer(int playerIndex);
		void CreateCoily() const;
	private:
		const int m_PlayerIndex;

	};
}
