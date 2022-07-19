#include <unordered_map>

#define LEFT_ARROW_KEY    SDLK_LEFT
#define RIGHT_ARROW_KEY   SDLK_RIGHT
#define UP_ARROW_KEY      SDLK_UP
#define DOWN_ARROW_KEY    SDLK_DOWN
#define ESCAPE_KEY        SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

// Classe "InputManager" que cuida do input do jogo
class InputManager {
	private:
		bool mouseState[6];
		int mouseUpdate[6];
		std::unordered_map<int, bool> keyState;
		std::unordered_map<int, int> keyUpdate;
		bool quitRequested;
		int updateCounter;
		int mouseX;
		int mouseY;

		InputManager();
		~InputManager();

	public:
		void Update();
		bool KeyPress(int key);
		bool KeyRelease(int key);
		bool IsKeyDown(int key);
		bool MousePress(int button);
		bool MouseRelease(int button);
		bool IsMouseDown(int button);
		int GetMouseX();
		int GetMouseY();
		bool QuitRequested();
		static InputManager& GetInstance();
};

#endif // INPUTMANAGER_H
