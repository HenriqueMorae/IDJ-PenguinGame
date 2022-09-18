#include "State.h"
#include "Music.h"

#ifndef ENDSTATE_H
#define ENDSTATE_H

// Classe "EndState"
class EndState : public State {
	private:
		Music* backgroundMusic;

	public:
		EndState();
		~EndState();
		void Start();
		void Pause();
		void Resume();
		void LoadAssets();
		void Update(float dt);
		void Render();
};

#endif // ENDSTATE_H
