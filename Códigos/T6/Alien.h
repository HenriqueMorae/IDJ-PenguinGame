#include <queue>
#include <memory>
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"

#ifndef ALIEN_H
#define ALIEN_H

// Classe "Alien"
// COMPONENT
class Alien : public Component {
	private:
		enum AlienState { MOVING, RESTING };
		AlienState state;
		Timer restTimer;
		Vec2 destination;
		Vec2 speed;
		Vec2 direcao;
		int hp;
		float rot;
		std::vector<std::weak_ptr<GameObject>> minionArray;

	public:
		static int alienCount;
		Alien(GameObject& associated, int nMinions);
		~Alien();
		void Start();
		void Update(float dt);
		void Render();
		bool Is(std::string type);
		void NotifyCollision(GameObject& other);
};

#endif // ALIEN_H
