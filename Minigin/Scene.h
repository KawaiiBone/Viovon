#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object/*, bool IsPlayer*/);

		void Update(float deltaTime);
		void Render() const;
		std::string GetSceneName()const;

		
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);
		void DestroyDeadObjects();

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		
		
		static unsigned int m_IdCounter; 
	};

}
