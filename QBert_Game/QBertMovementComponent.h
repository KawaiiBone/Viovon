#pragma once
#include <memory>
#include <string>
#include "BaseComponent.h"
#include "MapPartComponent.h"

namespace dae
{
	struct AxialCoordinates;
	class QBertMovementComponent final : public BaseComponent
	{
	public:
		QBertMovementComponent(GameObject* pBlockObject, int row, int collu);
		~QBertMovementComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() const override;
		void SubjectRender()const override;
		PlatformStatus GetPlatformStatus();
		AxialCoordinates GetCoordinates() ;
		void SetCoordinates(AxialCoordinates coordinates);
		bool IsMovementCooldownOver();
		glm::vec2 GetNewPosition();
		bool CanHandleMovement(GameObject* movQbert);
		void SetBlockObject( GameObject* pBlockObject);
		void Reset(GameObject& object) override;
	private:
		GameObject* m_pBlockObject;
		int m_Row;
		int m_Collum;
		Cooldown m_MovementCooldown;
		
		
		
	};

}