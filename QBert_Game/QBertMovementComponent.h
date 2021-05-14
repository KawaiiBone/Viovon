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
		QBertMovementComponent(GameObject* pBlockObject, int row, int collum);
		~QBertMovementComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void SubjectRender()const override;
		PlatformStatus GetPlatformStatus();
		AxialCoordinates GetCoordinates();
		void SetCoordinates(AxialCoordinates coordinates);

		glm::vec2 GetNewPosition();
		bool CanHandleMovement(GameObject* movQbert);
	private:
		void SetBlockObject( GameObject* pBlockObject);
		GameObject* m_pBlockObject;
		bool m_HasLostPlatform;
		int m_Row;
		int m_Collum;
		
		
	};

}