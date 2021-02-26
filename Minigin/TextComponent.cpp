#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"
#include "FPSComponent.h"
#include "Texture2D.h"



dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font, const SDL_Color color, bool isStaticTxt) :
	m_Text(text), m_Font(font), m_Texture(nullptr), m_Color(color), m_IsStaticTxt(isStaticTxt)
{


		//const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);

}

dae::TextComponent::TextComponent(const std::shared_ptr<Font>& font, const SDL_Color color)
: m_Font(font), m_Texture(nullptr), m_Color(color), m_IsStaticTxt(false), m_Text(nullptr)
{
	
}


void dae::TextComponent::Update(const std::string& string)
{

	if (m_IsStaticTxt)
	{
		return;
	}
	else if(m_Text != string)
	{
		m_Text = string;
		//const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
	}

}
void dae::TextComponent::Render(float x, float y) const
{
	if (m_Texture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, x, y);
	}
}

dae::TextComponent::~TextComponent()
{

}

