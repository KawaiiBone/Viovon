#pragma once
#include "RenderComponent.h"


namespace dae
{
	class Texture2D;
	class TextureComponent : public RenderComponent
	{
	public:
		TextureComponent(const std::string& filename);
		void Render(float x, float y) const override;
		void Update(const std::string& string) override;

		~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;
	private:

		std::shared_ptr<Texture2D> m_Texture;
		std::string m_FileName;

	};
}