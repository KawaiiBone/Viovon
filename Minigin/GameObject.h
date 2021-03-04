#pragma once
#include "Transform.h"
#include  <vector>
#include "Subject.h"

namespace dae
{
	class Texture2D;
	class RenderComponent;
	class BaseComponent;
	class Observer;
	
	class GameObject final
	{
	public:
		GameObject(float x, float y);
		GameObject(float x, float y, RenderComponent* pRender);
		GameObject(float x, float y, std::vector<BaseComponent*> bvComp , RenderComponent* pRender);
		GameObject(float x, float y, BaseComponent* bvComp, RenderComponent* pRender);
		
		void Update(float deltaTime) ;
		void Render() const ;
		void AddBaseComponent(BaseComponent* myComponent);
		void AddRenderComponent(RenderComponent* RenderComponent);
		void AddPairComponent(RenderComponent* RenderComponent,BaseComponent* myComponent);
		

		bool IsDead() const;
		void Die();
		


		void SetMovement(float x, float y);
		void SetVelocity(float x, float y);
		Transform GetVelocity()const;
		void ResetVelocity();
		

		Subject& GetSubject() ;
		void AddObeserver(Observer* pObs);
		
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <typename T>
		T* GetComponent() const
		{
			{
				for (BaseComponent* bc : m_VectorpBComponents)
				{
					if (dynamic_cast<T*>(bc))
						return (T*)bc;
				}
				return nullptr;
			}
		}
		

	private:
		Transform m_Velocity;
		Transform m_Pos;
		RenderComponent* m_pRenderComponent;
		std::vector<BaseComponent*> m_VectorpBComponents;
		bool m_IsDead;
		Subject m_subject;//dont put here create a sepperate class, also dont put it then in component
		// maybe add connected components: base compoenent + render component
		// 	std::vector<std::pair<RenderComponent*,BaseComponent*>>
		
		std::vector<std::pair<RenderComponent*, BaseComponent*>>  m_VectorCombinedComponents;
	};


	
}
