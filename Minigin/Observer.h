#pragma once
#include "Transform.h"
namespace dae
{
	class RenderComponent;
	class GameObject;
	enum class EventObeserver;
	
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(std::shared_ptr<dae::GameObject>, EventObeserver event) = 0;
		virtual  void Render() const = 0;
	};






	


}