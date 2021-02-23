#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextureComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(const std::string& filename):
		m_FileName{filename}, m_IsCostumForm{false}

{
	m_Texture = ResourceManager::GetInstance().LoadTexture(m_FileName);
}

dae::TextureComponent::TextureComponent(const std::string& filename, float width, float height):
	m_FileName{ filename }, m_IsCostumForm{ true }, m_Width(width), m_Height(height)
{
	
}

void dae::TextureComponent::Render(float x, float y) const
{
	if (m_Texture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, x, y);
	/*	if (m_IsCostumForm)
		{
			Renderer::GetInstance().RenderTexture(*m_Texture, x, y,m_Width,m_Height);
		}
		else
			Renderer::GetInstance().RenderTexture(*m_Texture, x, y);
		{
		}*/
	}
}

void dae::TextureComponent::Update(const std::string& string)
{
	if (string != "0" && string != m_FileName)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(m_FileName);
	}
	return;
}
