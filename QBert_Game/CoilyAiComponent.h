#pragma once



#include <memory>
#include <string>
//#include "BaseComponent.h"
#include "AIBaseComponent.h"
#include "MapPartComponent.h"


namespace dae
{
	struct AxialCoordinates;
	class CoilyAiComponent final : public AIBaseComponent
	{
	public:
		CoilyAiComponent(int maxRow, const std::vector<std::string>& vecTextureNames, float spawnTime);
		~CoilyAiComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() const override;
		void SubjectRender()const override;
		void Reset(GameObject& object) override;
	private:


		bool CanHandleMovement(GameObject* movQbert);
		void BallMovement(GameObject& object);
		void CoilyMovement(GameObject& object);

		bool m_IsInBallForm;


	};

}
