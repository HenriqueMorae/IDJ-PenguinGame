#include <vector>
#include <memory>
#include "Music.h"
#include "State.h"
#include "TileSet.h"
#include "GameObject.h"

#ifndef STAGESTATE_H
#define STAGESTATE_H

// Classe "StageState" que cuida da logica especifica do jogo
class StageState : public State {
	private:
		std::vector<std::shared_ptr<GameObject>> colliderArray;
		Music* backgroundMusic;
		TileSet* tileSet;

	public:
		StageState();
		~StageState();
		void Start();
		void Pause();
		void Resume();
		void LoadAssets();
		void Update(float dt);
		void Render();
};

#endif // STAGESTATE_H
