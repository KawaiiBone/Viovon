#pragma once
#include "Command.h"
#include "QBertComponentsHeaders.h"
namespace dae
{
	

class MoveLeftUp final : public Command
{
public:
	MoveLeftUp() {  };
	void Execute(std::shared_ptr<dae::GameObject> object) override
	{
		auto tmp = object->GetComponent<QBertMovementComponent>();
		if(tmp->CanHandleMovement(MovementQbert::leftUp))
		{
			object->SetPosition(tmp->GetNewPosition().x, tmp->GetNewPosition().y);
			//std::cout << "leftUp\n";


			if (tmp->GetPlatformStatus() == PlatformStatus::gainedStatus)
			{
				object->GetComponent<ScoreComponent>()->OnPlatform(object, true);
			}
			else if (tmp->GetPlatformStatus() == PlatformStatus::lostStatus)
			{
				object->GetComponent<ScoreComponent>()->OnPlatform(object, false);
			}
		}
	

	}
};
class MoveRightUp final : public Command
{
public:
	MoveRightUp() { };
	void Execute(std::shared_ptr<dae::GameObject> object) override
	{
		auto tmp = object->GetComponent<QBertMovementComponent>();
		if(tmp->CanHandleMovement(MovementQbert::rightUp))
		{
			object->SetPosition(tmp->GetNewPosition().x, tmp->GetNewPosition().y);
			//std::cout << "rightUp\n";


			if (tmp->GetPlatformStatus() == PlatformStatus::gainedStatus)
			{
				object->GetComponent<ScoreComponent>()->OnPlatform(object, true);
			}
			else if (tmp->GetPlatformStatus() == PlatformStatus::lostStatus)
			{
				object->GetComponent<ScoreComponent>()->OnPlatform(object, false);
			}
		}
	}
};

class MoveRightDown final : public Command
{
public:
	MoveRightDown() {  };
	void Execute(std::shared_ptr<dae::GameObject> object) override
	{
		auto tmp = object->GetComponent<QBertMovementComponent>();
		if(tmp->CanHandleMovement(MovementQbert::RightDown))
		{
			
			object->SetPosition(tmp->GetNewPosition().x, tmp->GetNewPosition().y);
			//std::cout << "RightDown\n";


			if (tmp->GetPlatformStatus() == PlatformStatus::gainedStatus)
			{
				object->GetComponent<ScoreComponent>()->OnPlatform(object, true);
			}
			else if(tmp->GetPlatformStatus() == PlatformStatus::lostStatus)
			{
				object->GetComponent<ScoreComponent>()->OnPlatform(object, false);
			}
		
	
		
		}
	

	}
};
class MoveLeftDown final : public Command
{
public:
	MoveLeftDown() { };
	void Execute(std::shared_ptr<dae::GameObject> object) override
	{
		auto tmp = object->GetComponent<QBertMovementComponent>();
		if(tmp->CanHandleMovement(MovementQbert::leftDown))
		{
			object->SetPosition(tmp->GetNewPosition().x, tmp->GetNewPosition().y);
			//std::cout << "leftDown\n";


			if (tmp->GetPlatformStatus() == PlatformStatus::gainedStatus)
			{
				object->GetComponent<ScoreComponent>()->OnPlatform(object, true);
			}
			else if (tmp->GetPlatformStatus() == PlatformStatus::lostStatus)
			{
				object->GetComponent<ScoreComponent>()->OnPlatform(object, false);
			}
		}
	}
};
	
}