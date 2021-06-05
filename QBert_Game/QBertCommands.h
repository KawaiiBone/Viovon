#pragma once
#include "Command.h"
#include "QBertComponentsHeaders.h"
#include "Scene.h"
#include "SceneManager.h"
namespace dae
{


	class MoveLeftUp final : public Command
	{
	private:
		const int m_Score{ 25 };
		const AxialCoordinates  M_StartCoordinates{ 6,0 };
	public:
		MoveLeftUp() = default;
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{


			auto scene = SceneManager::GetInstance().GetCurrentScene();
			auto playerObjectComp = object->GetComponent<PLayerComponent>();
			//auto playerObjectComp = object->GetComponent<QBertMovementComponent>();
			auto mapPartObject = scene->GetMapPart(playerObjectComp->GetCoordinates().row, playerObjectComp->GetCoordinates().collum - 1);

			if (mapPartObject.second && playerObjectComp->IsMovementCooldownOver())
			{
				playerObjectComp->CanHandleMovement(mapPartObject.second);
				
				 auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();

			

				object->SetPosition(playerObjectComp->GetNewPosition().x, playerObjectComp->GetNewPosition().y);
				
				if (mapPartObjectComp->IsBlock())
				{
					playerObjectComp->SetCoordinates(mapPartObject.first);
					
				}
				else
				{
					
					playerObjectComp->SetCoordinates({ M_StartCoordinates });
				}



				
				auto tmpScoreComp = object->GetComponent<ScoreComponent>();
				if (playerObjectComp->GetPlatformStatus() == PlatformStatus::gainedStatus)
				{
					tmpScoreComp->InfluenceScore(m_Score, object);
					if (scene->HasFinishedLevel())
					{
						TypeOfScene tmpTypeScene{ scene->GetSceneName() };
						if (tmpTypeScene != TypeOfScene::level3)
						{
							tmpTypeScene = static_cast<TypeOfScene>(static_cast<int>(tmpTypeScene) + 1);
							SceneManager::GetInstance().ChangeScene(tmpTypeScene);
						}
						else
						{
							SceneManager::GetInstance().ChangeScene(TypeOfScene::startMenu);
							SceneManager::GetInstance().ResetScenes();
						}
					}

				}
				else if (playerObjectComp->GetPlatformStatus() == PlatformStatus::lostStatus)
				{
					tmpScoreComp->InfluenceScore(-m_Score, object);

				}
				playerObjectComp->PLaySound();
			}
			else if (playerObjectComp->IsMovementCooldownOver())
			{
				playerObjectComp->ResetCooldown();
				auto tmpLiveComp = object->GetComponent<LivesComponent>();
				if (tmpLiveComp)
				{
					object->GetComponent<LivesComponent>()->InfluenceLife(-1, object);
				}
			
			}




		}
	};
	class MoveRightUp final : public Command
	{
	private:
		const int m_Score{ 25 };
		const AxialCoordinates  M_StartCoordinates{ 6,0 };
	public:
		MoveRightUp() = default;
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{

			auto scene = SceneManager::GetInstance().GetCurrentScene();
			auto playerObjectComp = object->GetComponent<PLayerComponent>();
			//auto playerObjectComp = object->GetComponent<QBertMovementComponent>();
			auto mapPartObject = scene->GetMapPart(playerObjectComp->GetCoordinates().row + 1, playerObjectComp->GetCoordinates().collum - 1);

			if (mapPartObject.second && playerObjectComp->IsMovementCooldownOver())
			{
				
				playerObjectComp->CanHandleMovement(mapPartObject.second);
				
		
				auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();
				object->SetPosition(playerObjectComp->GetNewPosition().x, playerObjectComp->GetNewPosition().y);


				
				if (mapPartObjectComp->IsBlock())
				{
					playerObjectComp->SetCoordinates(mapPartObject.first);
				}
				else
				{
					playerObjectComp->SetCoordinates(M_StartCoordinates);
				}
			


				auto tmpScoreComp = object->GetComponent<ScoreComponent>();
				if (playerObjectComp->GetPlatformStatus() == PlatformStatus::gainedStatus)
				{
					tmpScoreComp->InfluenceScore(m_Score, object);
					if (scene->HasFinishedLevel())
					{
						TypeOfScene tmpTypeScene{ scene->GetSceneName() };
						if (tmpTypeScene != TypeOfScene::level3)
						{
							tmpTypeScene = static_cast<TypeOfScene>(static_cast<int>(tmpTypeScene) + 1);
							SceneManager::GetInstance().ChangeScene(tmpTypeScene);
						}
						else
						{
							SceneManager::GetInstance().ChangeScene(TypeOfScene::startMenu);
							SceneManager::GetInstance().ResetScenes();
						}
					}

				}
				else if (playerObjectComp->GetPlatformStatus() == PlatformStatus::lostStatus)
				{
					tmpScoreComp->InfluenceScore(-m_Score, object);

				}
				playerObjectComp->PLaySound();
			}
			else if (playerObjectComp->IsMovementCooldownOver())
			{
				playerObjectComp->ResetCooldown();
				auto tmpLiveComp = object->GetComponent<LivesComponent>();
				if (tmpLiveComp)
				{
					object->GetComponent<LivesComponent>()->InfluenceLife(-1, object);
				}

			}
		
		}
	};

	class MoveRightDown final : public Command
	{
	private:
		const int m_Score{ 25 };
	public:
		MoveRightDown() = default;
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{



			auto scene = SceneManager::GetInstance().GetCurrentScene();
			auto playerObjectComp = object->GetComponent<PLayerComponent>();
			//auto playerObjectComp = object->GetComponent<QBertMovementComponent>();
			auto mapPartObject = scene->GetMapPart(playerObjectComp->GetCoordinates().row, playerObjectComp->GetCoordinates().collum + 1);

			if (mapPartObject.second && playerObjectComp->IsMovementCooldownOver())
			{
				auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();

				playerObjectComp->CanHandleMovement(mapPartObject.second );

				
				object->SetPosition(mapPartObjectComp->GetPlatformPos().x, mapPartObjectComp->GetPlatformPos().y);
				playerObjectComp->SetCoordinates(mapPartObject.first);





				auto tmpScoreComp = object->GetComponent<ScoreComponent>();
				if (playerObjectComp->GetPlatformStatus() == PlatformStatus::gainedStatus)
				{
					
					tmpScoreComp->InfluenceScore(m_Score, object);
					if (scene->HasFinishedLevel())
					{
						TypeOfScene tmpTypeScene{ scene->GetSceneName() };
						if (tmpTypeScene != TypeOfScene::level3)
						{
							tmpTypeScene = static_cast<TypeOfScene>(static_cast<int>(tmpTypeScene) + 1);
							SceneManager::GetInstance().ChangeScene(tmpTypeScene);
						}
						else
						{
							SceneManager::GetInstance().ChangeScene(TypeOfScene::startMenu);
							SceneManager::GetInstance().ResetScenes();
						}
					}
				}
				else if (playerObjectComp->GetPlatformStatus() == PlatformStatus::lostStatus)
				{
					tmpScoreComp->InfluenceScore(-m_Score, object);

				}
				playerObjectComp->PLaySound();
			}
			else if(playerObjectComp->IsMovementCooldownOver())
			{
				playerObjectComp->ResetCooldown();
				auto tmpLiveComp = object->GetComponent<LivesComponent>();
				if (tmpLiveComp)
				{
					object->GetComponent<LivesComponent>()->InfluenceLife(-1, object);
				}

			}
	

		}
	};
	class MoveLeftDown final : public Command
	{
	private:
		const int m_Score{ 25 };
	public:
		MoveLeftDown() = default;
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{

			auto scene = SceneManager::GetInstance().GetCurrentScene();
			auto playerObjectComp = object->GetComponent<PLayerComponent>();
			//auto playerObjectComp = object->GetComponent<QBertMovementComponent>();
			auto mapPartObject = scene->GetMapPart((playerObjectComp->GetCoordinates().row - 1), (playerObjectComp->GetCoordinates().collum + 1));

			if (mapPartObject.second && playerObjectComp->IsMovementCooldownOver())
			{
				auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();

				playerObjectComp->CanHandleMovement(mapPartObject.second );
				
				object->SetPosition(mapPartObjectComp->GetPlatformPos().x, mapPartObjectComp->GetPlatformPos().y);
				playerObjectComp->SetCoordinates(mapPartObject.first);





				auto tmpScoreComp = object->GetComponent<ScoreComponent>();
				if (playerObjectComp->GetPlatformStatus() == PlatformStatus::gainedStatus)
				{
					tmpScoreComp->InfluenceScore(m_Score, object);
					if (scene->HasFinishedLevel())
					{
						TypeOfScene tmpTypeScene{ scene->GetSceneName() };
						if (tmpTypeScene != TypeOfScene::level3)
						{
							tmpTypeScene = static_cast<TypeOfScene>(static_cast<int>(tmpTypeScene) + 1);
							SceneManager::GetInstance().ChangeScene(tmpTypeScene);
						}
						else
						{
							SceneManager::GetInstance().ChangeScene(TypeOfScene::startMenu);
							SceneManager::GetInstance().ResetScenes();
						}
					}

				}
				else if (playerObjectComp->GetPlatformStatus() == PlatformStatus::lostStatus)
				{
					tmpScoreComp->InfluenceScore(-m_Score, object);

				}
				playerObjectComp->PLaySound();
			}
			else if (playerObjectComp->IsMovementCooldownOver())
			{
				playerObjectComp->ResetCooldown();
				auto tmpLiveComp = object->GetComponent<LivesComponent>();
				if (tmpLiveComp)
				{
					object->GetComponent<LivesComponent>()->InfluenceLife(-1, object);
				}

			}

		}
	};

}