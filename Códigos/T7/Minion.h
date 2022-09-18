#include "Component.h"
#include "GameObject.h"

#ifndef MINION_H
#define MINION_H

// Classe "Minion"
// COMPONENT
class Minion : public Component {
	private:
		std::weak_ptr<GameObject> alienCenter;
		float arc;
		float rot;

	public:
		Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
		void Boom();
		void Update(float dt);
		void Render();
		bool Is(std::string type);
		void Shoot(Vec2 target);
};

#endif // MINION_H
