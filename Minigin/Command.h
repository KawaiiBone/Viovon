#pragma once
#include "Windows.h"
#include <iostream>
#include "GameObject.h"
#include "QuitComponent.h"
#include "PlayerMovement.h"
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
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			std::cout << object->IsDead() << " jump!\n";

		}
	};


	class Fire : public Command
	{
	public:
		Fire() { };
		~Fire() = default;
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			std::cout << object->IsDead() << "fire!\n";

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
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			std::cout << object->IsDead() << "Crouch!\n";
		}
	};

	class Die : public Command
	{
	public:
		Die() {  };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			object->Die();
			//std::cout << object->Die() << " jump!\n";

		}
	};




	class MoveLeft : public Command
	{
	public:
		MoveLeft() {  };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{


			object->SetXAxisVelocity(-800.f);// to test

		}
	};
	class MoveRight : public Command
	{
	public:
		MoveRight() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			object->SetXAxisVelocity(800.f);// to test
		}
	};

	class MoveUp : public Command
	{
	public:
		MoveUp() {  };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{


			object->SetYAxisVelocity(-800.f);// to test

		}
	};
	class MoveDown : public Command
	{
	public:
		MoveDown() { };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			object->SetYAxisVelocity(800.f);// to test
		}
	};
}