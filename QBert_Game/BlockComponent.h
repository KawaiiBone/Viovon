#pragma once
#include <string>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)


#include <memory>
#include <vector>


#include "BaseComponent.h"



namespace dae
{
	class GameObject;
	enum class MovementQbert
	{
		leftUp,
		leftDown,
		rightUp,
		RightDown,
		none
	};

	enum class PlatformStatus
	{
		gainedStatus,
		lostStatus,
		none
		
		
	};
	

	struct MovementPosBlock
	{
		MovementQbert MovQbert;
		//std::shared_ptr<GameObject> pBlockObject; //Change to weak pointers??? or put in raw pointers
		GameObject* pBlockObject;
	};
	
	class BlockComponent final : public BaseComponent
	{
	public:
		BlockComponent(float x, float y, const std::vector<MovementPosBlock>& movPosBlocksVec, const std::vector<std::string>& textureBlockNames, bool BlockPenalty);
		~BlockComponent();
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


}


