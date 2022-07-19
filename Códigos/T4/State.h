#include <vector>
#include <memory>
#include "SDL.h"
#include "GameObject.h"
#include "Music.h"

#ifndef STATE_H
#define STATE_H

// Classe "State" que cuida da logica especifica do jogo
class State {
	private:
		std::vector<std::unique_ptr<GameObject>> objectArray;
		Music* music;
		bool quitRequested;

		void AddObject(int mouseX, int mouseY);

	public:
		State();
		~State();
		bool QuitRequested();
		void LoadAssets();
		void Update(float dt);
		void Render();
};

#endif // STATE_H
