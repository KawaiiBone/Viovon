#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class GameObject;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(float deltaTime);
		void Render();
		
		std::vector < std::shared_ptr<GameObject>> GetPlayers();
		void AddPlayer(std::shared_ptr<GameObject>& object);
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::vector < std::shared_ptr<GameObject>> m_pPlayers;
	};
}
