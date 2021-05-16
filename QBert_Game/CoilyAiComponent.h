#pragma once



#include <memory>
#include <string>
//#include "BaseComponent.h"
#include "AIBaseComponent.h"
#include "MapPartComponent.h"


namespace dae
{
	struct AxialCoordinates;
	class CoilyAiComponent final : public AIBaseComponent
	{
	public:
		CoilyAiComponent(int maxRow, const std::vector<std::string>& vecTextureNames);
		~CoilyAiComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() override;
		void SubjectRender()const override;
	private:


		bool CanHandleMovement(GameObject* movQbert);
		void BallMovement(GameObject& object);
		void CoilyMovement(GameObject& object);

		bool m_IsInBallForm;


	};

}
//namespace dae
//{
//	struct AxialCoordinates;
//	class CoilyAiComponent final : public BaseComponent
//	{
//	public:
//		CoilyAiComponent(int maxRow, const std::vector<std::string>& vecTextureNames);
//		~CoilyAiComponent();
//		void Update(float deltaTime, GameObject& object) override;
//		std::string GetTxt() override;
//		void SubjectRender()const override;
//	private:
//		
//		void SetCoordinates(AxialCoordinates coordinates);
//		bool CanHandleMovement(GameObject* movQbert);
//		void BallMovement(GameObject& object);
//		void CoilyMovement(GameObject& object);
//		void SetBlockObject(GameObject* pBlockObject);
//		bool DidHitQBert();
//		GameObject* m_pBlockObject;
//		GameObject* m_QbertObject;
//		int m_Row;
//		int m_Collum;
//		Cooldown m_MovementCooldown;
//		std::vector<std::string> m_VecTextureNames;
//		int m_IndexTexturesNames;
//		bool m_IsInBallForm;
//
//
//	};
//
//}