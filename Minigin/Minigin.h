#pragma once



struct SDL_Window;
namespace dae
{
	struct WindowSize
	{
		int width{0};
		int height{0};
	};

	
	class InputManager;
	class SceneManager;
	class Scene;
	
	class Minigin
	{
	public:
		Minigin();
		void TestLoadGame(const int amountOfPLayers) const;
		void Cleanup();
		void Run();
		WindowSize GetWindowSize() const;
		void CreateDefaultCommandKeys();
	private:
		void Initialize();
		void AddPlayers(Scene& sceneMan, int totalPlayers) const;
		void CreateUI() const;
		void ProcessInput(bool& doContinue, SceneManager& sceneMan, InputManager& inputman);
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_pWindow{};
		const WindowSize m_WindowSize;
	};

	
}
