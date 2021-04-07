#pragma once
//#include "Transform.h"
#include "RenderComponent.h"
#include <SDL.h>



namespace dae
{
	class Font;
	class Texture2D;
	class FPSComponent;
	class TextComponent final : public RenderComponent
	{
	public:
		TextComponent(const std::string& text, const std::shared_ptr<Font>& font, const SDL_Color color, bool isStaticTxt);
		TextComponent(const std::shared_ptr<Font>& font, const SDL_Color color);
		void Update(const std::string& string) override;
		void Render(float x, float y) const override;


		~TextComponent();
		//TextComponent(const TextComponent& other) = delete;
		//TextComponent(TextComponent&& other) = delete;
		//TextComponent& operator=(const TextComponent& other) = delete;
		//TextComponent& operator=(TextComponent&& other) = delete;
	private:

		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		SDL_Color m_Color;
		bool m_IsStaticTxt;
	};
}