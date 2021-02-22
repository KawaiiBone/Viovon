#pragma once
#include "Transform.h"
#include  <vector>


namespace dae
{
	class Texture2D;
	class RenderComponent;
	class BaseComponent;
	
	class GameObject final
	{
	public:
		
		GameObject(float x, float y, RenderComponent* pRender);
		GameObject(float x, float y, std::vector<BaseComponent*> bvComp , RenderComponent* pRender);
		GameObject(float x, float y, BaseComponent* bvComp, RenderComponent* pRender);
		
		void Update(float deltaTime) ;
		void Render() const ;

		 ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		RenderComponent* m_pRender;
		std::vector<BaseComponent*> m_VectorpBComponents;
		
	};
}
