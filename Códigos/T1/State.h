#include "SDL.h"
#include "Sprite.h"
#include "Music.h"

#ifndef STATE_H
#define STATE_H

// Classe "State" que cuida da logica especifica do jogo
class State {
	private:
		Sprite* bg;
		Music* music;
		bool quitRequested;

	public:
		State();
		bool QuitRequested();
		void LoadAssets();
		void Update(float dt);
		void Render();
};

#endif // STATE_H
