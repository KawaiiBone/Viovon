#pragma once
#include "Windows.h"
#include <iostream>
#include "GameObject.h"
#include "ComponentsHeaders.h"
#include "ServiceLocater.h"

namespace dae
{

	class Command
	{
	public:

		virtual ~Command() = default;
		virtual void Execute(std::shared_ptr<dae::GameObject> object) = 0;

	private:


	};


	class Jump final : public Command
	{
	public:
		Jump() { };
		void Execute(std::shared_ptr<dae::GameObject> ) override
		{
			

		}
	};


	class Fire final : public Command
	{
	public:
		Fire() { };
		~Fire() = default;
		void Execute(std::shared_ptr<dae::GameObject> ) override
		{
		

		}
	};

	class Quit final : public Command
	{
	public:
		Quit() {  };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			object->GetComponent<QuitComponent>()->Quit();
		}
	};

	class Crouch final : public Command
	{
	public:
		Crouch() { };
		void Execute(std::shared_ptr<dae::GameObject> ) override
		{
		}
	};

	class Die final : public Command
	{
	public:
		Die() {  };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{

			object->Die();
		}
	};







	class GainLife final : public Command// for testing
	{
	public:
		GainLife() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			if (object->GetComponent<LivesComponent>())
			{
				object->GetComponent<LivesComponent>()->InfluenceLife(5, object);

			}
		}
	};

	class LoseLife final : public Command// for testing
	{
	public:
		LoseLife() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			if (object->GetComponent<LivesComponent>())
			{
				object->GetComponent<LivesComponent>()->InfluenceLife(-5, object);
			}
		}
	};



	class IncreaseScore final : public Command//for testing
	{
	public:
		IncreaseScore() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			if (object->GetComponent<LivesComponent>())
			{
				auto& a = ServiceLocater::GetSoundSystem();
				a.PlaySound("../Data/sounds/door1.wav", 100);//it works!!!
				object->GetComponent<ScoreComponent>()->InfluenceScore(+5, object);
			}
		}
	};

	class DecreaseScore final : public Command// for testing
	{
	public:
		DecreaseScore() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			if (object->GetComponent<LivesComponent>())
			{
				auto& a = ServiceLocater::GetSoundSystem();
				a.PlaySound("../Data/sounds/door2.wav", 100);//it works!!!
				object->GetComponent<ScoreComponent>()->InfluenceScore(-5, object);
			}
		}
	};
}