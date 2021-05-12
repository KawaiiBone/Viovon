#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const TypeOfScene typescene);
	public:
		void Add(const std::shared_ptr<GameObject>& object/*, bool IsPlayer*/);

		void Update(float deltaTime);
		void Render() const;
		TypeOfScene GetSceneName()const;

		
		
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const TypeOfScene typescene);
		void DestroyDeadObjects();

		const TypeOfScene  m_TypeScene;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		
		
		static unsigned int m_IdCounter; 
	};

}
