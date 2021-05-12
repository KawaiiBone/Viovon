#pragma once
#include <memory>

namespace dae
{
	class Scene;
	class GameObject;
	class QBert
	{
	public:
		QBert();
	void LoadQbert(Scene& sceneMan, float StartPosx, float StartPosy, GameObject* pblockObject);
	private:

	};
}
