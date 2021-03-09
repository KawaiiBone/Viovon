#pragma once

namespace dae
{
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