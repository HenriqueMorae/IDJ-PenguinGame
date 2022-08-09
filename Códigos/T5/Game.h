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
		State* state;
		int frameStart;
		float dt;

		Game(std::string title, int width, int height);
		void CalculateDeltaTime();

	public:
		~Game();
		void Run();
		SDL_Renderer* GetRenderer();
		State& GetState();
		static Game& GetInstance();
		float GetDeltaTime();
};

#endif // GAME_H
