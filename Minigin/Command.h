#pragma once
#include "Windows.h"
#include <iostream>
namespace dae
{
	typedef unsigned int        UINT;
	class Command
	{
	public:
	
		virtual ~Command() = default;
		virtual void Execute(bool& run/*will change parameter when put in to engine*/) = 0;
		UINT GetButton() { return m_Button; };
		void SetButton(UINT button) { m_Button = button; };
	private:
		UINT m_Button{ 0x1000 };
		
	};


	class Jump : public Command
	{
	public:
		Jump(UINT button) { Command::SetButton(button); };
		void Execute(bool& run/*will change parameter when put in to engine*/) override
		{
			std::cout << run << " jump!\n";
			
		}
	};


	class Fire : public Command
	{
	public:
		Fire(UINT button) { Command::SetButton(button); };
		~Fire() = default;
		void Execute(bool& run/*will change parameter when put in to engine*/) override
		{
			std::cout << run << "fire!\n";
		
		}
	};

	class Quit : public Command
	{
	public:
		Quit(UINT button) { Command::SetButton(button); };
		void Execute(bool& run/*will change parameter when put in to engine*/) override
		{
			run = false;
			std::cout << run << "i quit!\n";
		}
	};

	class Crouch : public Command
	{
	public:
		Crouch(UINT button) { Command::SetButton(button); };
		void Execute(bool& run/*will change parameter when put in to engine*/) override
		{
			std::cout << run << "Crouch!\n";
		}
	};
}