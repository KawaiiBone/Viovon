#pragma once

namespace dae
{

	struct Cooldown
	{
		const float cooldownDuration;
		float cooldownCounter;
		bool cooldownOver;
		
		Cooldown(const float cDDur, float cDCount = 0.f, bool cDOver = true):
			cooldownDuration(cDDur), cooldownCounter(cDCount), cooldownOver(cDOver)
		{
			
		}
		
	};

	
	class GameObject;
	class BaseComponent
	{
	public:

		virtual ~BaseComponent() = default;
		virtual  void Update(float deltaTime, GameObject& object) = 0;
		virtual std::string GetTxt() = 0;
		virtual void SubjectRender()const  = 0;
	};
}