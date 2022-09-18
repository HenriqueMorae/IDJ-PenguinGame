#include <stack>
#include <string>
#include "SDL.h"

#include "State.h"

#ifndef GAME_H
#define GAME_H

// Classe "Game" que controla recursos, game loop e states
class Game {
	private:
		static Game* instance;
		SDL_Window* window;
		SDL_Renderer* renderer;
		State* storedState;
		int frameStart;
		float dt;
		std::stack<std::unique_ptr<State>> stateStack;

		void CalculateDeltaTime();

	public:
		Game(std::string title, int width, int height);
		~Game();
		void Run();
		SDL_Renderer* GetRenderer();
		State& GetCurrentState();
		static Game& GetInstance();
		float GetDeltaTime();
		void Push(State* state);
};

#endif // GAME_H
