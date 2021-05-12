#pragma once
#include "Singleton.h"

namespace dae
{
	enum class TypeOfScene
	{
		startMenu,
		pauseMenu,
		level1,
		level2,
		level3,
		demo,
		none
	};

	

	
	class Scene;
	class GameObject;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const TypeOfScene typeScene);
		std::shared_ptr<Scene> GetPointerScene( const TypeOfScene sceneNam );

		void Update(float deltaTime);
		void Render() const;
		
		std::vector < std::shared_ptr<GameObject>> GetPlayers();
		void AddPlayer(std::shared_ptr<GameObject>& object);
		
		void ChangeScene(const TypeOfScene typeScene);
	
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		
	//	std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::vector<std::pair<std::shared_ptr<Scene>,TypeOfScene>> m_Scenes;
		
		std::vector < std::shared_ptr<GameObject>> m_pPlayers;
		int m_ScenesVecIndex{ 0 };
	};
}
