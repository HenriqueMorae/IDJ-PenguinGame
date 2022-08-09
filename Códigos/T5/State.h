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
		std::vector<std::shared_ptr<GameObject>> objectArray;
		Music* music;
		bool quitRequested;
		bool started;

	public:
		State();
		~State();
		void Start();
		bool QuitRequested();
		void LoadAssets();
		void Update(float dt);
		void Render();
		std::weak_ptr<GameObject> AddObject(GameObject* go);
		std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
};

#endif // STATE_H
