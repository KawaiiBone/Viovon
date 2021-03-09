#pragma once
#include "Windows.h"
#include <iostream>
#include "GameObject.h"

#include "ComponentsHeaders.h"


namespace dae
{

	class Command
	{
	public:

		virtual ~Command() = default;
		virtual void Execute(std::shared_ptr<dae::GameObject> object) = 0;

	private:


	};


	class Jump : public Command
	{
	public:
		Jump() { };
		void Execute(std::shared_ptr<dae::GameObject> ) override
		{
			

		}
	};


	class Fire : public Command
	{
	public:
		Fire() { };
		~Fire() = default;
		void Execute(std::shared_ptr<dae::GameObject> ) override
		{
		

		}
	};

	class Quit : public Command
	{
	public:
		Quit() {  };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			object->GetComponent<QuitComponent>()->Quit();
		}
	};

	class Crouch : public Command
	{
	public:
		Crouch() { };
		void Execute(std::shared_ptr<dae::GameObject> ) override
		{
		}
	};

	class Die : public Command
	{
	public:
		Die() {  };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{

			object->Die();
		}
	};




	class MoveLeft : public Command
	{
	public:
		MoveLeft() {  };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{


			object->SetVelocity(-800.f,0 );// to test

		}
	};
	class MoveRight : public Command
	{
	public:
		MoveRight() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			object->SetVelocity(800.f,0);// to test
		}
	};

	class MoveUp : public Command
	{
	public:
		MoveUp() {  };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{


			object->SetVelocity( 0,-800.f);// to test

		}
	};
	class MoveDown : public Command
	{
	public:
		MoveDown() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			object->SetVelocity( 0,800.f);
			
		}
	};


	class GainHp : public Command// for testing
	{
	public:
		GainHp() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			if (object->GetComponent<HealthComponent>())
			{
				object->GetComponent<HealthComponent>()->InfluenceHealth(5, object);

			}
		}
	};

	class LoseHp : public Command// for testing
	{
	public:
		LoseHp() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			if (object->GetComponent<HealthComponent>())
			{
				object->GetComponent<HealthComponent>()->InfluenceHealth(-5, object);
			}
		}
	};



	class IncreaseScore : public Command//for testing
	{
	public:
		IncreaseScore() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			if (object->GetComponent<HealthComponent>())
			{
				object->GetComponent<ScoreComponent>()->InfluenceScore(+5, object);
			}
		}
	};

	class DecreaseScore : public Command// for testing
	{
	public:
		DecreaseScore() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			if (object->GetComponent<HealthComponent>())
			{
				object->GetComponent<ScoreComponent>()->InfluenceScore(-5, object);
			}
		}
	};
}