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

	enum class PlatformStatus
	{
		gainedStatus,
		lostStatus,
		none


	};



	class MapPartComponent : public BaseComponent
	{
	public:
		MapPartComponent(float x, float y, const std::vector<std::string>& textureBlockName, bool isblock);
		virtual ~MapPartComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void SubjectRender()const override;
		glm::vec2 GetPlatformPos() const;
		virtual	GameObject* HandleQbertMovement(GameObject* movQbert);

		PlatformStatus GetPlatformStatus();
		bool IsBlock();


	protected:
		bool PlusNamesVecIndex();
		bool MinusNamesVecIndex();
		void SetPlatformStatus(PlatformStatus platStatus);
		virtual void ChangeMovementPosBlock(GameObject* movBlock) = 0;// maybe change


	private:
		const glm::vec2 m_PlatformPos;
		std::vector<std::string> m_TextureBlockNames;
		int m_NamesVecIndex;
		PlatformStatus m_PlatformStatus;
		const bool m_IsBlock;

	};


	
	/*class GameObject;
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
		GameObject* pBlockObject;
	};

	class MapPartComponent : public BaseComponent
	{
	public:
		MapPartComponent(float x, float y, const std::vector<MovementPosBlock>& movPosBlocksVec, const std::vector<std::string>& textureBlockName, bool isblock);
		virtual ~MapPartComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void SubjectRender()const override;
		glm::vec2 GetPlatformPos() const;
		virtual	GameObject* HandleQbertMovement(MovementQbert movQbert);
		 void AddMovementPosBlock(const MovementPosBlock& MovPosBlock);
		PlatformStatus GetPlatformStatus();
		bool IsBlock();


	protected:
		bool PlusNamesVecIndex();
		bool MinusNamesVecIndex();
		void SetPlatformStatus(PlatformStatus platStatus);
		virtual void ChangeMovementPosBlock(GameObject* movBlock) = 0;// maybe change

	
	private:
		const glm::vec2 m_PlatformPos;
		std::vector<MovementPosBlock> m_MovPosBlocksVec;
		std::vector<std::string> m_TextureBlockNames;
		int m_NamesVecIndex;
		PlatformStatus m_PlatformStatus;
		const bool m_IsBlock;

	};*/


}