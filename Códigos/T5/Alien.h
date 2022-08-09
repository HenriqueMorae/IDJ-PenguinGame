#include <queue>
#include <memory>
#include "Component.h"
#include "Vec2.h"

#ifndef ALIEN_H
#define ALIEN_H

// Classe "Alien"
// COMPONENT
class Alien : public Component {
	private:
		class Action {
			public:
				enum ActionType { MOVE, SHOOT };
				ActionType type;
				Vec2 pos;

				Action(ActionType type, float x, float y) {
					this->type = type;
					pos.x = x;
					pos.y = y;
				}
		};

		Vec2 speed;
		int hp;
		float rot;
		std::queue<Action> taskQueue;
		std::vector<std::weak_ptr<GameObject>> minionArray;

	public:
		Alien(GameObject& associated, int nMinions);
		~Alien();
		void Start();
		void Update(float dt);
		void Render();
		bool Is(std::string type);
};

#endif // ALIEN_H
