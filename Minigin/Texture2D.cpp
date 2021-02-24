#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}



SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	
	
	m_Texture = texture;
}



SDL_Point dae::Texture2D::getsize()
{

	SDL_Point size;
	SDL_QueryTexture(m_Texture, NULL, NULL, &size.x, &size.y);
	return size;

}