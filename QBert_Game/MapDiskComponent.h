#pragma once


#include "MapPartComponent.h"


namespace dae
{
	class GameObject;

	class MapDiskComponent final : public MapPartComponent
	{
	public:
		MapDiskComponent(float x, float y);
		~MapDiskComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void SubjectRender()const override;
		GameObject* HandleQbertMovement(GameObject* movQbert) override;





		void ChangeMovementPosBlock(GameObject* movBlock) override;
	private:
		


	};


	//class MapDiskComponent final : public MapPartComponent
	//{
	//public:
	//	MapDiskComponent(float x, float y, const std::vector<MovementPosBlock>& movPosBlocksVec, const std::vector<std::string>& textureBlockNames);
	//	~MapDiskComponent();
	//	void Update(float deltaTime, GameObject& object) override;
	//	std::string GetTxt() override;
	//	void SubjectRender()const override;
	//	GameObject* HandleQbertMovement(MovementQbert movQbert) override;
	//	
	//	



	//	void ChangeMovementPosBlock(GameObject* movBlock ) override;
	//private:
	//	GameObject* m_HighestBlock;

	//	
	//};

}