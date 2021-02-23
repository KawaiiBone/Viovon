#pragma once
#include "Windows.h"
#include <iostream>
#include "GameObject.h"
#include "QuitComponent.h"
namespace dae
{
	typedef unsigned int        UINT;
	class Command
	{
	public:
	
		virtual ~Command() = default;
		virtual void Execute(std::shared_ptr<dae::GameObject> object) = 0;
		UINT GetButton() { return m_Button; };
		void SetButton(UINT button) { m_Button = button; };
	private:
		UINT m_Button{ 0x1000 };
		
	};


	class Jump : public Command
	{
	public:
		Jump(UINT button) { Command::SetButton(button); };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			std::cout << object->IsDead() << " jump!\n";
			
		}
	};


	class Fire : public Command
	{
	public:
		Fire(UINT button) { Command::SetButton(button); };
		~Fire() = default;
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			std::cout << object->IsDead() << "fire!\n";
		
		}
	};

	class Quit : public Command
	{
	public:
		Quit(UINT button) { Command::SetButton(button); };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			object->GetComponent<QuitComponent>()->Quit();
		}
	};

	class Crouch : public Command
	{
	public:
		Crouch(UINT button) { Command::SetButton(button); };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			std::cout << object->IsDead() << "Crouch!\n";
		}
	};

	class Die : public Command
	{
	public:
		Die(UINT button) { Command::SetButton(button); };
		void Execute(std::shared_ptr<dae::GameObject> object) override
		{
			object->Die();
			//std::cout << object->Die() << " jump!\n";

		}
	};
}