#pragma once
#include <memory>
#include <string>
#include "PLayerComponent.h"
#include "MapPartComponent.h"

namespace dae
{
	struct AxialCoordinates;
	class PLayerCoilyComponent final: public PLayerComponent
	{
	public:
		PLayerCoilyComponent(GameObject* pBlockObject, int row, int collu, const std::vector<std::string>& textureNicknames, const std::string& soundPath);
		  ~PLayerCoilyComponent() = default;
		  void Update(float deltaTime, GameObject& object) override;
		  std::string GetTxt() const override;
		  PlatformStatus GetPlatformStatus() override;
		  void SubjectRender()const override;
		  void Reset(GameObject& object) override;
	private:
		void BallMovement(GameObject& object);
		std::shared_ptr<dae::GameObject> DidHitQBert() const;
		const PlatformStatus m_PlatStatus;
		bool m_IsInBallForm;
		std::vector<std::string> m_VecTextureNames;
		int m_IndexTexturesNames;
		Cooldown m_BallMoveCooldown;

	};
}