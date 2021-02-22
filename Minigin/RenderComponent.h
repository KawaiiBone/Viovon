#pragma once
#include "BaseComponent.h"
namespace dae
{
	//class Texture2D;
	
	class RenderComponent 
	{
	public:
		RenderComponent() = default;
		virtual void Render(float x, float y) const  = 0 ;
		virtual void Update(const std::string& string)  =0;
		virtual ~RenderComponent() = default;

	};
}


