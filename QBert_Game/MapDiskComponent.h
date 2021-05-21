#pragma once


#include "MapPartComponent.h"


namespace dae
{
	class GameObject;

	class MapDiskComponent final : public MapPartComponent
	{
	public:
		MapDiskComponent(float x, float y, float width, float height);
		~MapDiskComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() const override;
		void SubjectRender()const override;
		GameObject* HandleQbertMovement(GameObject* movQbert) override;
		void Reset(GameObject& object) override;





		void ChangeMovementPosBlock(GameObject* movBlock) override;
	private:
		


	};




}