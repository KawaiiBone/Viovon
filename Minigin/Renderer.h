#pragma once
#include "Singleton.h"
#include "InterfaceWindow.h"
struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */

	//class InterfaceWindow;
	enum class InterFaceNames;
	
	class Renderer final : public Singleton<Renderer>
	{
	public:
		Renderer();
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

		void AddInterfaceWindow(InterfaceWindow interFaceWindow);
	private:

		void DifficultyInterface();
		
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window;
		std::vector<InterfaceWindow> m_InterfaceWindowsVec;
		InterFaceNames m_InterFaceWindowName;
	};


}

