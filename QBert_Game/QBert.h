#pragma once
#include <memory>
#include <GameObject.h>
namespace dae
{
	class Scene;
	class QBert
	{
	public:
		QBert(int playerIndex);
		void CreateQbert();
	private:
		const int m_PlayerIndex;
	};
}
