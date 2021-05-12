#pragma once
#include <memory>
#include <string>
#include "BaseComponent.h"
#include "BlockComponent.h"

namespace dae
{
	
	class QBertMovementComponent final : public BaseComponent
	{
	public:
		QBertMovementComponent(GameObject* pBlockObject);
		~QBertMovementComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void SubjectRender()const override;
		PlatformStatus GetPlatformStatus();

		glm::vec2 GetNewPosition();
		bool CanHandleMovement(MovementQbert movQbert);
	private:
		void SetBlockObject( GameObject* pBlockObject);
		GameObject* m_pBlockObject;
		bool m_HasLostPlatform;
	};

}