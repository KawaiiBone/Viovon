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
		MapBlockComponent(float x, float y, const std::vector<std::string>& textureBlockNames, bool BlockPenalty);
		~MapBlockComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void SubjectRender()const override;
		GameObject* HandleQbertMovement(GameObject* movQbert) override;


		void NextBlockTexture();
		void PenaltyChangeBlockTexture();



		void ChangeMovementPosBlock(GameObject* movBlock) override;
	private:
		const bool M_HasBlockPenalty;


	};
//class MapBlockComponent final : public MapPartComponent
//	{
//	public:
//		MapBlockComponent(float x, float y, const std::vector<MovementPosBlock>&movPosBlocksVec, const std::vector<std::string>&textureBlockNames, bool BlockPenalty);
//		~MapBlockComponent();
//		void Update(float deltaTime, GameObject& object) override;
//		std::string GetTxt() override;
//		void SubjectRender()const override;
//		GameObject* HandleQbertMovement(MovementQbert movQbert) override;
//		
//	
//		void NextBlockTexture();
//		void PenaltyChangeBlockTexture();
//
//
//
//		void ChangeMovementPosBlock(GameObject* movBlock) override;
//	private:
//	const bool M_HasBlockPenalty;
//
//
//	};


	
}











//enum class MovementQbert
	//{
	//	leftUp,
	//	leftDown,
	//	rightUp,
	//	RightDown,
	//	none
	//};

	//enum class PlatformStatus
	//{
	//	gainedStatus,
	//	lostStatus,
	//	none
	//	
	//	
	//};
	//

	//struct MovementPosBlock
	//{
	//	MovementQbert MovQbert;
	//	//std::shared_ptr<GameObject> pBlockObject; //Change to weak pointers??? or put in raw pointers
	//	GameObject* pBlockObject;
	//};

	/*class MapBlockComponent final : public BaseComponent
	{
	public:
		MapBlockComponent(float x, float y, const std::vector<MovementPosBlock>& movPosBlocksVec, const std::vector<std::string>& textureBlockNames, bool BlockPenalty);
		~MapBlockComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void SubjectRender()const override;
		glm::vec2 GetPlatformPos() const;
		GameObject* HandleQbertMovement(MovementQbert movQbert);
		void AddMovementPosBlock(const MovementPosBlock& MovPosBlock);
		void NextBlockTexture();
		void ThirdLvlChangeBlockTexture();
		PlatformStatus GetPlatformStatus();



	private:
		glm::vec2 m_PlatformPos;
		std::vector<MovementPosBlock> m_MovPosBlocksVec;
		std::vector<std::string> m_TextureBlockNames;
		int m_NamesVecIndex;
		const bool M_HasBlockPenalty;
		PlatformStatus m_platformStatus;

	};


}*/