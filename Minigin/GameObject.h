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
		void AddComponent(BaseComponent* myComponent);

	
		bool IsDead();
		void Die();
	
		
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;



		template <typename T>
		T* GetComponent()
		{
			{
				for (BaseComponent* bc : m_VectorpBComponents)
				{
					if (reinterpret_cast<T*>(bc))
						return (T*)bc;
				}
				return nullptr;
			}
		}
		

	private:
		Transform m_Transform;
		RenderComponent* m_pRender;
		std::vector<BaseComponent*> m_VectorpBComponents;
		bool m_IsDead;
		
	};


	
}
