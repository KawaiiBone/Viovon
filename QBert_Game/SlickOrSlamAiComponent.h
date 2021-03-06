﻿#pragma once

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
		SlickOrSlamAiComponent(int maxRow, const std::vector<std::string>& vecTextureNames, float spawnTime, const std::string& soundPath);
		~SlickOrSlamAiComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() const override;
		void SubjectRender()const override;
		void Reset(GameObject& object) override;
	private:


		
		void Movement(GameObject& object);
		const int m_DieScore;


	};
}