#include "QbertTexturesComponent.h"
#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Texture2D.h"
#include "ResourceManager.h"

dae::QbertTexturesComponent::QbertTexturesComponent(float scale):
	 m_Width(0.f), m_Height(0.f), m_VecIndex{0}, m_Scale(scale)
{
}

dae::QbertTexturesComponent::QbertTexturesComponent(float scale,
	const std::vector<std::pair<std::string, std::string>>& filenamesAndNickNames):
	m_Width(0.f), m_Height(0.f), m_VecIndex{ 0 }, m_Scale(scale)
{
	for (std::pair<std::string, std::string> element : filenamesAndNickNames)
	{
		m_VecTextures.push_back({ ResourceManager::GetInstance().LoadTexture(element.first),element.second });
	}
	
	m_Width = float(m_VecTextures[0].first->getsize().x) * m_Scale;
	m_Height = float(m_VecTextures[0].first->getsize().y) * m_Scale;
}


void dae::QbertTexturesComponent::AddTexture(const std::string& filename, const std::string& givenName)
	
{

	m_VecTextures.push_back({ ResourceManager::GetInstance().LoadTexture(filename),givenName });
	
	m_Width = float(m_VecTextures[0].first->getsize().x) * m_Scale;
	m_Height = float(m_VecTextures[0].first->getsize().y) * m_Scale;


	
}

void dae::QbertTexturesComponent::Render(float x, float y) const
{


	Renderer::GetInstance().RenderTexture(*m_VecTextures[m_VecIndex].first, x, y, m_Width, m_Height);

	
}

void dae::QbertTexturesComponent::Update(const std::string& string)
{

	for (size_t i = 0; i < m_VecTextures.size(); ++i)
	{
		if (string == m_VecTextures[i].second)
		{
			m_VecIndex = int(i);
		}
	}
	
}

float dae::QbertTexturesComponent::GetWidth()
{
	return m_Width;
}

float dae::QbertTexturesComponent::GetHeight()
{
	return m_Height;
}