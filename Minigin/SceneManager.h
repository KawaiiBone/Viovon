#pragma once
#include "Singleton.h"
#include <memory>
#include <vector>
namespace dae
{
	enum class TypeOfScene
	{
		startMenu,
		pauseMenu,
		demo,
		level1,
		level2,
		level3,
		none
	};

	enum class GameMode
	{
		singleplayer,
		coop,
		versus,
		none

		
	};
	

	
	class Scene;
	class GameObject;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const TypeOfScene typeScene);
		std::shared_ptr<Scene> GetPointerScene( const TypeOfScene sceneNam );
		std::shared_ptr<Scene> GetCurrentScene();
		void Update(float deltaTime);
		void Render() const;
		
		std::vector < std::shared_ptr<GameObject>> GetPlayers();
		void AddPlayer(std::shared_ptr<GameObject>& object);
		
		void ChangeScene(const TypeOfScene typeScene, bool fromSelectLevel);
		void SetGameMode(GameMode gameMode);
		GameMode GetGameMode()const ;
		void ResetScenes();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::pair<std::shared_ptr<Scene>,TypeOfScene>> m_Scenes;
		std::vector < std::shared_ptr<GameObject>> m_pPlayers;
		int m_ScenesVecIndex{ 0 };
		GameMode m_GameMode{ GameMode::none };
	};
}
