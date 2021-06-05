#pragma once
#include <memory>
#include <string>
#include "BaseComponent.h"
#include "MapPartComponent.h"

namespace dae
{
	struct AxialCoordinates;
	class PLayerComponent : public BaseComponent
	{
	public:
		PLayerComponent(GameObject* pBlockObject, int row, int collu, const std::string& soundPath);
		virtual ~PLayerComponent();
		void Update(float deltaTime, GameObject& object) override;
		std::string GetTxt() const override;
		void SubjectRender()const override;
		virtual  PlatformStatus GetPlatformStatus();
		AxialCoordinates GetCoordinates() const;
		AxialCoordinates GetOldCoordinates() const;
		void SetCoordinates(AxialCoordinates coordinates);
		bool IsMovementCooldownOver();
		glm::vec2 GetNewPosition();
		bool CanHandleMovement(GameObject* movQbert);
		void SetBlockObject(GameObject* pBlockObject);
		void Reset(GameObject& object) override;
		void PLaySound() const;
	protected:
		void ResetCooldown();
	private:
	
		GameObject* m_pBlockObject;
		int m_Row;
		int m_Collum;
		int m_OldRow;
		int m_OldCollum;
		Cooldown m_MovementCooldown;
		const std::string m_Text;
		const int m_StartingRow;
		const int m_StartingCollum;
		const std::string m_SoundPath;
		const int m_Volume;


	};

}