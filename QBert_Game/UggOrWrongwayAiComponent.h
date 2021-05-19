#pragma once
#include <memory>
#include <string>
#include "AIBaseComponent.h"
#include "MapPartComponent.h"


namespace dae
{
	struct AxialCoordinates;
	class UggOrWrongwayAiComponent final : public AIBaseComponent
	{
	public:
		UggOrWrongwayAiComponent(int maxRow, const std::vector<std::string>& vecTextureNames, float spawnTime);
		~UggOrWrongwayAiComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void SubjectRender()const override;
	private:

		void Movement(GameObject& object);


		bool m_StartedLeft;
	};
}