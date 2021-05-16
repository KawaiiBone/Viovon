#pragma once

#include <memory>
#include <string>
//#include "BaseComponent.h"
#include "AIBaseComponent.h"
#include "MapPartComponent.h"


namespace dae
{
	struct AxialCoordinates;
	class SlickOrSlamAiComponent final : public AIBaseComponent
	{
	public:
		SlickOrSlamAiComponent(int maxRow, const std::vector<std::string>& vecTextureNames);
		~SlickOrSlamAiComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void SubjectRender()const override;
	private:


		bool CanHandleMovement(GameObject* movQbert);
		void Movement(GameObject& object);


	};
}