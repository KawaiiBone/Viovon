#pragma once
#include "Command.h"
#include "QBertComponentsHeaders.h"
#include "Scene.h"
#include "SceneManager.h"
namespace dae
{


	class MoveLeftUp final : public Command
	{
	public:
		MoveLeftUp() {  };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{


			auto scene = SceneManager::GetInstance().GetPointerScene(TypeOfScene::demo);
			auto playerObjectComp = object->GetComponent<QBertMovementComponent>();
			auto mapPartObject = scene->GetMapPart(playerObjectComp->GetCoordinates().row, playerObjectComp->GetCoordinates().collum - 1);

			if (mapPartObject.second)
			{
				auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();

				object->SetPosition(mapPartObjectComp->GetPlatformPos().x, mapPartObjectComp->GetPlatformPos().y);
				playerObjectComp->SetCoordinates(mapPartObject.first);

				playerObjectComp->CanHandleMovement(mapPartObject.second);
				
			

				auto tmpScoreComp = object->GetComponent<ScoreComponent>();
				if (playerObjectComp->GetPlatformStatus() == PlatformStatus::gainedStatus)
				{
					tmpScoreComp->OnPlatform(object, true);
					tmpScoreComp->InfluenceScore(25, object);

				}
				else if (playerObjectComp->GetPlatformStatus() == PlatformStatus::lostStatus)
				{
					tmpScoreComp->OnPlatform(object, false);
					tmpScoreComp->InfluenceScore(-25, object);

				}

			}




			//auto tmp = object->GetComponent<QBertMovementComponent>();
			//if (tmp->CanHandleMovement(MovementQbert::leftUp))
			//{
			//	object->SetPosition(tmp->GetNewPosition().x, tmp->GetNewPosition().y);
			//	//std::cout << "leftUp\n";


			//	auto tmpScoreComp = object->GetComponent<ScoreComponent>();
			//	if (tmp->GetPlatformStatus() == PlatformStatus::gainedStatus)
			//	{
			//		tmpScoreComp->OnPlatform(object, true);
			//		tmpScoreComp->InfluenceScore(25, object);

			//	}
			//	else if (tmp->GetPlatformStatus() == PlatformStatus::lostStatus)
			//	{
			//		tmpScoreComp->OnPlatform(object, false);
			//		tmpScoreComp->InfluenceScore(-25, object);

			//	}
			//}


		}
	};
	class MoveRightUp final : public Command
	{
	public:
		MoveRightUp() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{

			auto scene = SceneManager::GetInstance().GetPointerScene(TypeOfScene::demo);
			auto playerObjectComp = object->GetComponent<QBertMovementComponent>();
			auto mapPartObject = scene->GetMapPart(playerObjectComp->GetCoordinates().row + 1, playerObjectComp->GetCoordinates().collum - 1);

			if (mapPartObject.second)
			{
				auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();
				
				playerObjectComp->CanHandleMovement(mapPartObject.second);
				object->SetPosition(mapPartObjectComp->GetPlatformPos().x, mapPartObjectComp->GetPlatformPos().y);
				
				if (mapPartObjectComp->IsBlock())
				{
					playerObjectComp->SetCoordinates(mapPartObject.first);
				}
				else
				{
					playerObjectComp->SetCoordinates({6,0});
				}
			





				auto tmpScoreComp = object->GetComponent<ScoreComponent>();
				if (playerObjectComp->GetPlatformStatus() == PlatformStatus::gainedStatus)
				{
					tmpScoreComp->OnPlatform(object, true);
					tmpScoreComp->InfluenceScore(25, object);

				}
				else if (playerObjectComp->GetPlatformStatus() == PlatformStatus::lostStatus)
				{
					tmpScoreComp->OnPlatform(object, false);
					tmpScoreComp->InfluenceScore(-25, object);

				}
				
			}
			
			//auto tmp = object->GetComponent<QBertMovementComponent>();
			/*if (tmp->CanHandleMovement(MovementQbert::rightUp))
			{

				object->SetPosition(tmp->GetNewPosition().x, tmp->GetNewPosition().y);



				auto tmpScoreComp = object->GetComponent<ScoreComponent>();
				if (tmp->GetPlatformStatus() == PlatformStatus::gainedStatus)
				{
					tmpScoreComp->OnPlatform(object, true);
					tmpScoreComp->InfluenceScore(25, object);

				}
				else if (tmp->GetPlatformStatus() == PlatformStatus::lostStatus)
				{
					tmpScoreComp->OnPlatform(object, false);
					tmpScoreComp->InfluenceScore(-25, object);

				}
			}*/
		}
	};

	class MoveRightDown final : public Command
	{
	public:
		MoveRightDown() {  };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{



			auto scene = SceneManager::GetInstance().GetPointerScene(TypeOfScene::demo);
			auto playerObjectComp = object->GetComponent<QBertMovementComponent>();
			auto mapPartObject = scene->GetMapPart(playerObjectComp->GetCoordinates().row, playerObjectComp->GetCoordinates().collum + 1);

			if (mapPartObject.second)
			{
				auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();

				object->SetPosition(mapPartObjectComp->GetPlatformPos().x, mapPartObjectComp->GetPlatformPos().y);
				playerObjectComp->SetCoordinates(mapPartObject.first);


				playerObjectComp->CanHandleMovement(mapPartObject.second);



				auto tmpScoreComp = object->GetComponent<ScoreComponent>();
				if (playerObjectComp->GetPlatformStatus() == PlatformStatus::gainedStatus)
				{
					tmpScoreComp->OnPlatform(object, true);
					tmpScoreComp->InfluenceScore(25, object);

				}
				else if (playerObjectComp->GetPlatformStatus() == PlatformStatus::lostStatus)
				{
					tmpScoreComp->OnPlatform(object, false);
					tmpScoreComp->InfluenceScore(-25, object);

				}
			}
			//auto tmp = object->GetComponent<QBertMovementComponent>();
			//if (tmp->CanHandleMovement(MovementQbert::RightDown))
			//{

			//	object->SetPosition(tmp->GetNewPosition().x, tmp->GetNewPosition().y);
			//	//std::cout << "RightDown\n";

			//	auto tmpScoreComp = object->GetComponent<ScoreComponent>();
			//	if (tmp->GetPlatformStatus() == PlatformStatus::gainedStatus)
			//	{
			//		tmpScoreComp->OnPlatform(object, true);
			//		tmpScoreComp->InfluenceScore(25, object);

			//	}
			//	else if (tmp->GetPlatformStatus() == PlatformStatus::lostStatus)
			//	{
			//		tmpScoreComp->OnPlatform(object, false);
			//		tmpScoreComp->InfluenceScore(-25, object);

			//	}



			//}


		}
	};
	class MoveLeftDown final : public Command
	{
	public:
		MoveLeftDown() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{

			auto scene = SceneManager::GetInstance().GetPointerScene(TypeOfScene::demo);
			auto playerObjectComp = object->GetComponent<QBertMovementComponent>();
			auto mapPartObject = scene->GetMapPart(playerObjectComp->GetCoordinates().row - 1, playerObjectComp->GetCoordinates().collum + 1);

			if (mapPartObject.second)
			{
				auto mapPartObjectComp = mapPartObject.second->GetComponent<MapPartComponent>();

				object->SetPosition(mapPartObjectComp->GetPlatformPos().x, mapPartObjectComp->GetPlatformPos().y);
				playerObjectComp->SetCoordinates(mapPartObject.first);


				playerObjectComp->CanHandleMovement(mapPartObject.second);



				auto tmpScoreComp = object->GetComponent<ScoreComponent>();
				if (playerObjectComp->GetPlatformStatus() == PlatformStatus::gainedStatus)
				{
					tmpScoreComp->OnPlatform(object, true);
					tmpScoreComp->InfluenceScore(25, object);

				}
				else if (playerObjectComp->GetPlatformStatus() == PlatformStatus::lostStatus)
				{
					tmpScoreComp->OnPlatform(object, false);
					tmpScoreComp->InfluenceScore(-25, object);

				}
			}
			//auto tmp = object->GetComponent<QBertMovementComponent>();
			//if (tmp->CanHandleMovement(MovementQbert::leftDown))
			//{
			//	object->SetPosition(tmp->GetNewPosition().x, tmp->GetNewPosition().y);
			//	//std::cout << "leftDown\n";

			//	auto tmpScoreComp = object->GetComponent<ScoreComponent>();
			//	if (tmp->GetPlatformStatus() == PlatformStatus::gainedStatus)
			//	{
			//		tmpScoreComp->OnPlatform(object, true);
			//		tmpScoreComp->InfluenceScore(25, object);

			//	}
			//	else if (tmp->GetPlatformStatus() == PlatformStatus::lostStatus)
			//	{
			//		tmpScoreComp->OnPlatform(object, false);
			//		tmpScoreComp->InfluenceScore(-25, object);

			//	}
			//}
		}
	};

}