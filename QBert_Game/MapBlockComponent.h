#pragma once
//#include <string>
//#pragma warning(push)
//#pragma warning (disable:4201)
//#include <glm/glm.hpp>
//#pragma warning(pop)
//
//
//#include <memory>
//#include <vector>


//#include "BaseComponent.h"

#include "MapPartComponent.h"


namespace dae
{
	class GameObject;


	class MapBlockComponent final : public MapPartComponent
	{
	public:
		MapBlockComponent(float x, float y, float width, float height, const std::vector<std::string>& textureBlockNames, bool penalty);
		~MapBlockComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void SubjectRender()const override;
		GameObject* HandleQbertMovement(GameObject* movQbert) override;


		void NextBlockTexture();
		void PenaltyChangeBlockTexture();



		void ChangeMovementPosBlock(GameObject* movBlock) override;
	private:



	};
}