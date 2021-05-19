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
		MoveLeftUp() {  };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{


			auto scene = SceneManager::GetInstance().GetCurrentScene();
			auto playerObjectComp = object->GetComponent<QBertMovementComponent>();
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
					tmpScoreComp->OnPlatform(object, true);
					tmpScoreComp->InfluenceScore(m_Score, object);

				}
				else if (playerObjectComp->GetPlatformStatus() == PlatformStatus::lostStatus)
				{
					tmpScoreComp->OnPlatform(object, false);
					tmpScoreComp->InfluenceScore(-m_Score, object);

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
		MoveRightUp() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{

			auto scene = SceneManager::GetInstance().GetCurrentScene();
			auto playerObjectComp = object->GetComponent<QBertMovementComponent>();
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
					tmpScoreComp->OnPlatform(object, true);
					tmpScoreComp->InfluenceScore(m_Score, object);

				}
				else if (playerObjectComp->GetPlatformStatus() == PlatformStatus::lostStatus)
				{
					tmpScoreComp->OnPlatform(object, false);
					tmpScoreComp->InfluenceScore(-m_Score, object);

				}
				
			}
		
		}
	};

	class MoveRightDown final : public Command
	{
	private:
		const int m_Score{ 25 };
	public:
		MoveRightDown() {  };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{



			auto scene = SceneManager::GetInstance().GetCurrentScene();
			auto playerObjectComp = object->GetComponent<QBertMovementComponent>();
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
					tmpScoreComp->OnPlatform(object, true);
					tmpScoreComp->InfluenceScore(m_Score, object);

				}
				else if (playerObjectComp->GetPlatformStatus() == PlatformStatus::lostStatus)
				{
					tmpScoreComp->OnPlatform(object, false);
					tmpScoreComp->InfluenceScore(-m_Score, object);

				}
			}
	


		}
	};
	class MoveLeftDown final : public Command
	{
	private:
		const int m_Score{ 25 };
	public:
		MoveLeftDown() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{

			auto scene = SceneManager::GetInstance().GetCurrentScene();
			auto playerObjectComp = object->GetComponent<QBertMovementComponent>();
			auto mapPartObject = scene->GetMapPart(playerObjectComp->GetCoordinates().row - 1, playerObjectComp->GetCoordinates().collum + 1);

			if (mapPartObject.second && playerObjectComp->IsMovementCooldownOver())
			{
				auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();

				playerObjectComp->CanHandleMovement(mapPartObject.second );
				
				object->SetPosition(mapPartObjectComp->GetPlatformPos().x, mapPartObjectComp->GetPlatformPos().y);
				playerObjectComp->SetCoordinates(mapPartObject.first);





				auto tmpScoreComp = object->GetComponent<ScoreComponent>();
				if (playerObjectComp->GetPlatformStatus() == PlatformStatus::gainedStatus)
				{
					tmpScoreComp->OnPlatform(object, true);
					tmpScoreComp->InfluenceScore(m_Score, object);

				}
				else if (playerObjectComp->GetPlatformStatus() == PlatformStatus::lostStatus)
				{
					tmpScoreComp->OnPlatform(object, false);
					tmpScoreComp->InfluenceScore(-m_Score, object);

				}
			}

		}
	};

}