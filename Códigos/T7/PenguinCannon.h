#include <memory>
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"

#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

// Classe "PenguinCannon"
// COMPONENT
class PenguinCannon : public Component {
	private:
		std::weak_ptr<GameObject> pbody;
		float angle;
		Vec2 direcao;
		Vec2 mouse;
		Timer* tempo;

	public:
		PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
		void Shoot();
		void Update(float dt);
		void Render();
		bool Is(std::string type);
};

#endif // PENGUINCANNON_H
