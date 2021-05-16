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
		QBertMovementComponent(GameObject* pBlockObject, int row, int collu, bool blockPenalty);
		~QBertMovementComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void SubjectRender()const override;
		PlatformStatus GetPlatformStatus();
		AxialCoordinates GetCoordinates();
		void SetCoordinates(AxialCoordinates coordinates);
		bool IsMovementCooldownOver();
		bool HasBlockPenalty();
		glm::vec2 GetNewPosition();
		bool CanHandleMovement(GameObject* movQbert, bool penaltyBlock);
	private:
		void SetBlockObject( GameObject* pBlockObject);
		GameObject* m_pBlockObject;
		int m_Row;
		int m_Collum;
		Cooldown m_MovementCooldown;
		const bool m_BlockPenalty;
		
		
		
	};

}