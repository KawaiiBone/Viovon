#pragma once

class AIBaseComponent
{
public:
	
};
#include <memory>
#include <string>
#include "BaseComponent.h"
#include "MapPartComponent.h"

namespace dae
{
	struct AxialCoordinates;
	class AIBaseComponent  : public BaseComponent
	{
	public:
		AIBaseComponent(int row, int collum, float cooldownDuration, const std::vector<std::string>& vecTextureNames);
		virtual ~AIBaseComponent();
		void Update(float deltaTime, GameObject& object) override = 0;
		std::string GetTxt() override;
		void SubjectRender()const override = 0;

	protected:
		AxialCoordinates GetCoordinates() const;
		GameObject* GetPQBertObject() const;
		void SetCoordinates(AxialCoordinates coordinates);
		bool CanHandleMovement(GameObject* movQbert);
		void SetBlockObject(GameObject* pBlockObject);
		bool DidHitQBert() const;
		void ResetCooldownCounter();
		bool IsInCooldown(float deltaTime);
		void NextTexture();
	private:
		GameObject* m_pBlockObject;
		GameObject* m_QbertObject;
		int m_Row;
		int m_Collum;
		Cooldown m_MovementCooldown;
		std::vector<std::string> m_VecTextureNames;
		int m_IndexTexturesNames;
		
	};

}
	