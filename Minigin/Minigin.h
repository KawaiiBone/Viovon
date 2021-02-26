#pragma once
struct SDL_Window;
namespace dae
{
	
	class InputManager;
	class SceneManager;
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		void CreateDefaultCommandKeys(InputManager& inputman);
		void ProcessInput(bool& doContinue, SceneManager& sceneMan, InputManager& inputman);
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};

	
}
