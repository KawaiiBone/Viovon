#pragma once
namespace dae
{
	class QBert
	{
	public:
		QBert(int playerIndex);
		void CreateQbert()const;
	private:
		const int m_PlayerIndex;
	};
}
