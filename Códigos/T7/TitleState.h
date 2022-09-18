#include "State.h"
#include "Timer.h"
#include "GameObject.h"

#ifndef TITLESTATE_H
#define TITLESTATE_H

// Classe "TitleState"
class TitleState : public State {
	private:
		Timer timerText;
		GameObject* tt;
		bool off;

	public:
		TitleState();
		~TitleState();
		void Start();
		void Pause();
		void Resume();
		void LoadAssets();
		void Update(float dt);
		void Render();
};

#endif // TITLESTATE_H
