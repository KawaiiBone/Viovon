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
		AIBaseComponent(int row, int collum, float cooldownDuration, const std::vector<std::string>& vecTextureNames, float spawnTime, const std::string& soundPath);
		virtual ~AIBaseComponent();
		void Update(float deltaTime, GameObject& object) override = 0;
		std::string GetTxt() const override;
		void SubjectRender()const override = 0;
		void Reset(GameObject& object) override;

	protected:
		AxialCoordinates GetCoordinates() const;
		GameObject* GetPQBertObject() const;
		void SetCoordinates(AxialCoordinates coordinates);
		void SetBlockObject(GameObject* pBlockObject);
		std::shared_ptr<dae::GameObject> DidHitQBert() const;
		void ResetCooldownCounter();
		bool IsInMovementCooldown(float deltaTime);
		bool IsInSpawnCooldown(float deltaTime, GameObject& object);
		void NextTexture();
		void Respawn( GameObject& object);
		void PlaySound()const;
	private:
		GameObject* m_pBlockObject;
		GameObject* m_QbertObject;
		int m_Row;
		int m_Collum;
		Cooldown m_MovementCooldown;
		std::vector<std::string> m_VecTextureNames;
		int m_IndexTexturesNames;
		Cooldown m_SpawnCooldown;
		const int m_StartingRow;
		const int m_StartingCollum;
		const std::string m_SoundPath;
		const int m_Volume;
	};

}
	