#pragma once

#include <memory>
#include <string>
#include <vector>


#include "RenderComponent.h"


namespace dae
{
	
	class Texture2D;
	class QbertTexturesComponent final : public RenderComponent
	{
	public:
		QbertTexturesComponent(float scale);
		QbertTexturesComponent(float scale, const std::vector<std::pair<std::string, std::string>>& filenamesAndNickNames);
		void AddTexture(const std::string& filename,const std::string& givenName);
		
		
		void Render(float x, float y) const override;
		void Update(const std::string& string) override;
		float GetWidth();
		float GetHeight();

		~QbertTexturesComponent() = default;
		QbertTexturesComponent(const QbertTexturesComponent& other) = delete;
		QbertTexturesComponent(QbertTexturesComponent&& other) = delete;
		QbertTexturesComponent& operator=(const QbertTexturesComponent& other) = delete;
		QbertTexturesComponent& operator=(QbertTexturesComponent&& other) = delete;
	private:

		std::vector<std::pair<std::shared_ptr<Texture2D>, std::string>> m_VecTextures;

		int m_VecIndex;

		float m_Width;
		float m_Height;
		const float m_Scale;


	};
}