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
		MapPartComponent(float x, float y, float width, float height, const std::vector<std::string>& textureBlockName, bool isblock, bool hasPenalty);
		virtual ~MapPartComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void SubjectRender()const override;
		glm::vec2 GetPlatformPos() const;
		virtual	GameObject* HandleQbertMovement(GameObject* movQbert);
		void HandleAiMovement();
		PlatformStatus GetPlatformStatus();
		bool IsBlock();
		glm::vec2 GetUggPlatformPos() const;
		glm::vec2 GetWrongWayPlatformPos() const;

		bool PlatformDone() ;
	protected:
		bool PlusNamesVecIndex();
		bool MinusNamesVecIndex();
		void SetPlatformStatus(PlatformStatus platStatus);
		virtual void ChangeMovementPosBlock(GameObject* movBlock) = 0;
		bool HasPenalty();

	private:
		const glm::vec2 m_PlatformPos;
		std::vector<std::string> m_TextureBlockNames;
		int m_NamesVecIndex;
		const glm::vec2 m_WrongwayPlatformPos;
		const glm::vec2 m_UggPlatformPos;
		PlatformStatus m_PlatformStatus;
		const bool m_IsBlock;
		const bool m_Penalty;
		

	};


	


}