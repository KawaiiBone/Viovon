﻿#pragma once


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
		std::string GetTxt() override;
		void SubjectRender()const override;
		GameObject* HandleQbertMovement(GameObject* movQbert, bool penaltyBlock) override;





		void ChangeMovementPosBlock(GameObject* movBlock, bool penaltyBlock) override;
	private:
		


	};




}